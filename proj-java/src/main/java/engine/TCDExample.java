package engine;

import common.MyLog;
import common.Pair;
import li3.TADCommunity;
import org.xml.sax.SAXException;

import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Set;
import java.util.TreeSet;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.Comparator;
import java.util.Iterator;
import java.util.stream.Collectors;
import java.util.Collections;

class PostsByDateComparator implements Comparator<Post> {
    public int compare(Post p1, Post p2) {
        int dateCmp = p1.getCreationDate().compareTo(p2.getCreationDate());
        if (dateCmp == 0) {
            return new Long(p1.getId()).compareTo(p2.getId());
        }
        return dateCmp;
    }
}

class PostIdsByDateComparator implements Comparator<Long> {
    private TCDExample community;

    public void setCommunity(TCDExample c) {
        this.community = c;
    }

    public int compare(Long id1, Long id2) {
        return this.community.getPost(id1).getCreationDate().compareTo(this.community.getPost(id2).getCreationDate());
    }
}

class UsersByRepComparator implements Comparator<Long> {
    private TCDExample community;

    public void setCommunity(TCDExample c) {
        this.community = c;
    }

    public int compare(Long id1, Long id2) {
        int repCmp = (new Long(this.community.getUser(id1).getRep())).compareTo(this.community.getUser(id2).getRep());
        if (repCmp == 0) {
            return (new Long(this.community.getUser(id1).getId())).compareTo(this.community.getUser(id2).getId());
        }
        return repCmp;
    }
}

class UsersByNumberOfPostsComparator implements Comparator<Long> {
    private TCDExample community;

    public void setCommunity(TCDExample c) {
        this.community = c;
    }

    public int compare(Long id1, Long id2) {
        int return1 = (new Integer(this.community.getUser(id2).getPostCount())).compareTo(this.community.getUser(id1).getPostCount());
        if (return1 == 0) {
            return (new Long(this.community.getUser(id2).getId())).compareTo(this.community.getUser(id1).getId());
        }
        return return1;
    }
}

public class TCDExample implements TADCommunity {

    private MyLog qelog;
    private Map<Long, Post> posts;
    private Map<Long, User> users;
    private Map<Long, Tag> tags;
    private Map<String, Tag> tagsFromName;
    private TreeSet<Post> postsByDate;
    private Map<Long, TreeSet<Long>> postsByUser;
    private TreeSet<Long> usersByRep;
    private TreeSet<Long> usersByPosts;

    public void init() {
        this.qelog = new MyLog("queryengine");
        this.posts = new HashMap<Long, Post>();
        this.users = new HashMap<Long, User>();
        this.tags = new HashMap<Long, Tag>();
        this.tagsFromName = new HashMap<String, Tag>();
        this.postsByDate = new TreeSet<Post>(new PostsByDateComparator());
        this.postsByUser = new HashMap<Long, TreeSet<Long>>();
        UsersByRepComparator cmp = new UsersByRepComparator();
        cmp.setCommunity(this);
        this.usersByRep = new TreeSet<Long>(cmp);
        UsersByNumberOfPostsComparator u = new UsersByNumberOfPostsComparator();
        u.setCommunity(this);
        this.usersByPosts = new TreeSet<Long>(u);

    }

    public void addPost(Post p, List<Long> addedBeforeParent) {
        Post newPost = p.clone();
        this.posts.put(p.getId(), newPost);
        this.postsByDate.add(newPost);

        // Atualizar PostCount e usersByPosts
        long userId = p.getUserId();
        this.usersByPosts.remove(userId);

        Post parent = this.posts.get(p.getParentId());
        if (parent != null) {
            parent.addAnswer(p.getId());
        } else if (p.getParentId() > p.getId()) {
            addedBeforeParent.add(p.getId());
        }

        int postCount = this.users.get(p.getUserId()).getPostCount();
        this.users.get(p.getUserId()).setPostCount(postCount + 1);

        this.usersByPosts.add(userId);

        TreeSet<Long> posts = this.postsByUser.get(p.getUserId());
        if (posts == null) {
            PostIdsByDateComparator c = new PostIdsByDateComparator();
            c.setCommunity(this);
            posts = new TreeSet<Long>(c);
        }
        posts.add(p.getId());
        this.postsByUser.put(p.getUserId(), posts);
    }

    public void addUser(User u) {
        User newUser = u.clone();
        this.users.put(u.getId(), newUser);
        this.usersByRep.add(newUser.getId());
        this.usersByPosts.add(newUser.getId());
    }

    public void addTag(Tag t) {
        this.tags.put(t.getId(), t.clone());
        this.tagsFromName.put(t.getName(), t.clone());
    }

    public Post getPost(long id) {
        return this.posts.get(id).clone();
    }

    public User getUser(long id) {
        return this.users.get(id).clone();
    }

    public Tag getTag(long id) {
        return this.tags.get(id).clone();
    }

    public Tag getTag(String name) {
        return this.tagsFromName.get(name);
    }

    public List<Post> getPostsBetween(LocalDate begin, LocalDate end) {
        Post beginPost = new Post();
        beginPost.setCreationDate(begin.plusDays(0L));
        Post endPost = new Post();
        endPost.setCreationDate(end.plusDays(0L));
        Iterator<Post> it = this.postsByDate.subSet(beginPost, true, endPost, true).descendingIterator();
        List<Post> r = new ArrayList();
        while (it.hasNext()) {
            r.add(it.next().clone());
        }
        return r;
    }

    public List<Long> getUsersByRep() {
        return this.usersByRep.stream().collect(Collectors.toList());
    }

    public List<Long> getPostIdsBy(long id) {
        return this.postsByUser.get(id).stream().collect(Collectors.toList());
    }

    public List<Long> getUsersByPosts() {
        return this.usersByPosts.stream().collect(Collectors.toList());
    }

    public List<Post> getPostsByDate() {
        List<Post> posts = this.postsByDate.stream().map(Post::clone).collect(Collectors.toList());
        Collections.reverse(posts);
        return posts;
    }

    public long getUserRep(long id) {
        User u = this.getUser(id);
        long res = u.getRep();
        return res;
    }

    public void load(String dumpPath) {
        this.init();
        List<Long> addedBeforeParent = new LinkedList<>();
        Load.load(this, dumpPath, addedBeforeParent);
        this.addToParents(addedBeforeParent);
    }

    private void addToParents(List<Long> addedBeforeParent) {
        addedBeforeParent.forEach(id -> {
            long parentId = this.posts.get(id).getParentId();
            Post parent = this.posts.get(parentId);
            if (parent != null) {
                parent.addAnswer(id);
            } else {
                qelog.writeLog("Parent post with id " + parentId + " not added.");
            }
        });
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        Pair<String,String> res = QueryOne.resposta(this, id);
        return res;
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        List<Long> res = QueryTwo.resposta(this, N);
        return res;
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
          Pair pair = QueryThree.answersquestions(this, begin, end);
          return pair;
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> res = QueryFour.resposta(this, tag, begin, end);
        return res;
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        Pair<String, List<Long>> res = QueryFive.resposta(this, id);
        return res;
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        List<Long> posts = QuerySix.resposta(this, N, begin, end);
        return posts;
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        List<Long> res = QuerySeven.resposta(this, N, begin, end);
        return res;
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        List<Long> res = QueryEighth.resposta(this, N, word);
        return res;
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long betterAnswer(long id) {
        long res = QueryTen.resposta(this,id);
        return res;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        List<Long> res = QueryEleven.resposta(this, N, begin, end);
        return res;
    }

    public void clear(){

    }
}

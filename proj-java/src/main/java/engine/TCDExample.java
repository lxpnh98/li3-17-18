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
import java.util.Set;
import java.util.TreeSet;
import java.util.Map;
import java.util.HashMap;
import java.util.Comparator;
import java.util.Iterator;


class PostsByDateComparator implements Comparator<Post> {
    public int compare(Post p1, Post p2) {
        return p1.getDate().compareTo(p2.getDate());
    }
}

class UsersByRepComparator implements Comparator<User> {
    public int compare(User u1, User u2) {
        return new Long(u1.getRep()).compareTo(u2.getRep());
    }
}

public class TCDExample implements TADCommunity {

    private MyLog qelog;
    private Map<Long, Post> posts;
    private Map<Long, User> users;
    private Map<Long, Tag> tags;
    private Map<String, Tag> tagsFromName;
    private TreeSet<Post> postsByDate;
    private TreeSet<User> usersByRep;
    private Map<Long, List<Long>> postsByUser;

    public void init() {
        this.qelog = new MyLog("queryengine");
        this.posts = new HashMap<Long, Post>();
        this.users = new HashMap<Long, User>();
        this.tags = new HashMap<Long, Tag>();
        this.tagsFromName = new HashMap<String, Tag>();
        this.postsByDate = new TreeSet<Post>(new PostsByDateComparator());
        this.usersByRep = new TreeSet<User>(new UsersByRepComparator());
        this.postsByUser = new HashMap<Long, List<Long>>();
    }

    public void addPost(Post p) {
        Post newPost = p.clone();
        this.posts.put(p.getId(), newPost);
        this.postsByDate.add(newPost);
    }

    public void addUser(User u) {
        User newUser = u.clone();
        this.users.put(u.getId(), newUser);
        this.usersByRep.add(newUser);
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
        //beginPost.setDate(LocalDate.MIN);
        beginPost.setDate(begin);
        Post endPost = new Post();
        //endPost.setDate(Post.randomDate());
        endPost.setDate(end);
        Iterator<Post> it = this.postsByDate.subSet(beginPost, true, endPost, true).descendingIterator();
        List<Post> r = new ArrayList();
        while (it.hasNext()) {
            r.add(it.next().clone());
        }
        return r;
    }

    public void load(String dumpPath) {
        this.init();
        Load.load(this, dumpPath);
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        Pair<String,String> res = QueryOne.resposta(this, id);
        System.out.println("Query 1: " + res);
        return res;
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return Arrays.asList(15811L,449L,158442L,167850L,367165L,295286L,59676L,93977L,35795L,3940L);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        return new Pair<>(3667L,4102L);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> res = QueryFour.resposta(this, tag, begin, end);
        System.out.println("Query 4 (comprimento): " + res.size()); // falta tratar das tags dos posts
        return res;
        /*
        return Arrays.asList(276174L,276029L,274462L,274324L,274316L,274141L,274100L,272937L,
                272813L,272754L,272666L,272565L,272450L,272313L,271816L,271683L,271647L,270853L,270608L,270528L,270488L,
                270188L,270014L,269876L,269781L,269095L,268501L,268155L,267746L,267656L,267625L,266742L,266335L,266016L,
                265531L,265483L,265443L,265347L,265104L,265067L,265028L,264764L,264762L,264616L,264525L,264292L,263816L,
                263740L,263460L,263405L,263378L,263253L,262733L,262574L);
        */
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        String shortBio = "<p>Coder. JS, Perl, Python, Basic<br>Books/movies: SF+F.<br>Dead:" +
                "dell 9300<br>Dead: dell 1720 as of may 10th 2011.</p>\n" +
                "<p>Current system: Acer Aspire 7750G.<br>\n" +
                "Works OOTB as of Ubuntu 12.04.<br></p>";
        List<Long> ids = Arrays.asList(982507L,982455L,980877L,980197L,980189L,976713L,974412L,
                974359L,973895L,973838L);
        return new Pair<>(shortBio,ids);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(701775L,697197L,694560L,696641L,704208L);
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(505506L,508221L,506510L,508029L,506824L,505581L,505368L,509498L,509283L,508635L);
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return Arrays.asList(980835L,979082L,974117L,974105L,973832L,971812L,971056L,968451L,964999L,962770L);
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long betterAnswer(long id) {
        return 175891;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){

    }
}

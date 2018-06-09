package engine;

import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;
import java.util.concurrent.ThreadLocalRandom;
import java.util.Set;
import java.util.HashSet;
import java.time.LocalDateTime;

public class Post {
    private long id;
    private long userId;
    private long score;
    private long commentCount;
    private LocalDate creationDate;
    private PostType type;
    private long acceptedAnswer;
    private String userDisplayName;
    private String title;
    private List<Long> answers;
    private Set<String> tags;
    private long parentId;

    public Post() {
        this.id = -1;
        this.userId = -1;
        this.score = -1;
        this.commentCount = -1;
        this.type = PostType.OTHERS;
        this.acceptedAnswer = -1;
        this.userDisplayName = "";
        this.title = "";
        this.answers = new ArrayList<>();
        this.creationDate = Post.randomDate();
        this.tags = new HashSet<>();
        this.parentId = -1;
    }

    public Post(long id, long userId, long score, long commentCount,
                LocalDate creationDate, PostType type, long acceptedAnswer,
                String userDisplayName, String title, Set<String> tags,
                long parentId) {
        this.id = id;
        this.userId = userId;
        this.score = score;
        this.commentCount = commentCount;
        this.creationDate = creationDate;
        this.type = type;
        this.acceptedAnswer = acceptedAnswer;
        this.userDisplayName = userDisplayName;
        this.title = title;
        this.tags = tags;
        this.parentId = parentId;
        this.answers = new ArrayList<Long>();
        this.score = score;
        this.creationDate = creationDate;
        this.tags = tags; // fazer clone
        this.commentCount = commentCount;
    }

    public Post(Post p) {
        this.id = p.getId();
        this.userId = p.getUserId();
        this.score = p.getScore();
        this.commentCount = p.getCommentCount();
        this.creationDate = p.getCreationDate();
        this.type = p.getType();
        this.acceptedAnswer = p.getAcceptedAnswer();
        this.userDisplayName = p.getUserDisplayName();
        this.title = p.getTitle();
        this.tags = p.getTags();
        this.parentId = p.getParentId();
        //this.answers = p.getAnswers();
    }

    public long getId() {
        return this.id;
    }

    public long getUserId() {
        return this.userId;
    }

    public long getScore() {
        return this.score;
    }

    public long getCommentCount() {
        return this.commentCount;
    }

    public LocalDate getCreationDate() {
        return this.creationDate;
    }
    
    public PostType getType() {
        return this.type;
    }

    public long getAcceptedAnswer() {
        return this.acceptedAnswer;
    }

    public String getUserDisplayName() {
        return this.userDisplayName;
    }

    public String getTitle() {
        return this.title;
    }

    public Set<String> getTags() {
        return this.tags; // fazer clone
    }

    public long getParentId() {
        return this.parentId;
    }

    public List getAnswers() {
        return this.answers; // fazer clone
    }

    //Sets
    public void setId(long id) {
        this.id = id;
    }

    public void setUserId(long userId) {
        this.userId = userId;
    }

    public void setScore(long score) {
        this.score = score;
    }

    public void setCommentCount(long commentCount) {
        this.commentCount = commentCount;
    }

    public void setCreationDate(LocalDate d) {
        this.creationDate = d;
    }
    
    public void setType(PostType type) {
        this.type = type;
    }

    public void setAcceptedAnswer(long acceptedAnswer) {
        this.acceptedAnswer = acceptedAnswer;
    }

    public void setUserDisplayName(String userDisplayName) {
        this.userDisplayName = userDisplayName;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setTags(Set<String> tags) {
        for(String s : tags) {
            this.tags.add(s);
        }
    }

    public void setParentId(long parentId) {
        this.parentId = parentId;
    }

    public void addAnswer(long id) {
        this.answers.add(id);
    }

    public static LocalDate randomDate() { // temporário, só para testar enquanto não se tem datas
        long minDay = LocalDate.MIN.toEpochDay();
        long maxDay = LocalDate.MAX.toEpochDay();
        long randomDay = ThreadLocalRandom.current().nextLong(minDay, maxDay);
        return LocalDate.ofEpochDay(randomDay);
    }

    public boolean hasTag(String name) {
        return this.tags.contains(name);
    }

    public Post clone() {
        return new Post(this);
    }

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }
        if ((o == null) || (o.getClass() != this.getClass())) {
            return false;
        }
        Post p = (Post) o;
        return (this.id == p.getId());
    }

    public String toString() {
        return " Post =>\n Id: " + this.id;
    }
}

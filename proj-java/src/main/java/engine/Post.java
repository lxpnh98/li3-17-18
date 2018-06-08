package engine;

import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;
import java.util.concurrent.ThreadLocalRandom;
import java.util.Set;
import java.util.HashSet;

public class Post {
    private long id;
    private PostType type;
    private long acceptedAnswer;
    private long userId;
    private String userDisplayName;
    private String title;
    private long parentId;
    private List<Long> answers;
    private long score;
    private LocalDate creationDate;
    private Set<Long> tags;
    private long commentCount;

    public static LocalDate randomDate() { // temporário, só para testar enquanto não se tem datas
        long minDay = LocalDate.MIN.toEpochDay();
        long maxDay = LocalDate.MAX.toEpochDay();
        long randomDay = ThreadLocalRandom.current().nextLong(minDay, maxDay);
        return LocalDate.ofEpochDay(randomDay);
    }

    public Post() {
        this.id = -1;
        this.type = PostType.OTHERS;
        this.acceptedAnswer = -1;
        this.userId = -1;
        this.userDisplayName = "";
        this.title = "";
        this.parentId = 0;
        this.answers = new ArrayList<Long>();
        this.score = 0;
        this.creationDate = Post.randomDate();
        this.tags = new HashSet<>();
        this.commentCount = 0;
    }

    public Post(long id, PostType type, long acceptedAnswer, long userId,
                String userDisplayName, String title, long parentId,
                long score, String creationDate, Set<Long> tags, long commentCount) {
        this.id = id;
        this.type = type;
        this.acceptedAnswer = acceptedAnswer;
        this.userId = userId;
        this.userDisplayName = userDisplayName;
        this.title = title;
        this.parentId = parentId;
        this.answers = new ArrayList<Long>();
        this.score = score;
        this.creationDate = Post.randomDate();
         /* Date.fromString(creationDate); Metodo fromString() Deprecated */
        this.tags = tags; // fazer clone
        this.commentCount = commentCount;
    }

    public Post(Post p) {
        this.id = p.getId();
        this.type = p.getType();
        this.acceptedAnswer = p.getAcceptedAnswer();
        this.userId = p.getUserId();
        this.userDisplayName = p.getUserDisplayName();
        this.title = p.getTitle();
        this.parentId = p.getParentId();
        this.answers = p.getAnswers();
        this.score = p.getScore();
        this.creationDate = p.getDate();
        this.tags = p.getTags();
        this.commentCount = p.getCommentCount();
    }

    public long getId() {
        return this.id;
    }

    public PostType getType() {
        return this.type;
    }

    public long getAcceptedAnswer() {
        return this.acceptedAnswer;
    }

    public long getUserId() {
        return this.userId;
    }

    public String getUserDisplayName() {
        return this.userDisplayName;
    }

    public String getTitle() {
        return this.title;
    }

    public long getParentId() {
        return this.parentId;
    }

    public List getAnswers() {
        return this.answers; // fazer clone
    }

    public void addAnswer(long id) {
        this.answers.add(id);
    }

    public long getScore() {
        return this.score;
    }

    public LocalDate getDate() {
        return this.creationDate.plusDays(0L);
    }

    public void setDate(LocalDate d) {
        this.creationDate = d.plusDays(0L);
    }

    public boolean hasTag(long tagId) {
        return true;
        //return this.tags.contains(tagId);
    }

    public Set<Long> getTags() {
        return this.tags; // fazer clone
    }

    public long getCommentCount() {
        return this.commentCount;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setType(PostType type) {
        this.type = type;
    }

    public void setAcceptedAnswer(long acceptedAnswer) {
        this.acceptedAnswer = acceptedAnswer;
    }

    public void setUserId(long userId) {
        this.userId = userId;
    }

    public void setUserDisplayName(String userDisplayName) {
        this.userDisplayName = userDisplayName;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setParentId(long parentId) {
        this.parentId = parentId;
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

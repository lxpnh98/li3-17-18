public enum PostType {
    ANSWER, QUESTION
}

public class Post {
    private long id;
    private enum PostType type;
    private long AcceptedAnswer;
    private long userId;
    private String userDisplayName;
    private String title;
    private long parentId;
    private List<Long> answers;
    private long score;
    private Date creationDate;
    private List<Long> tags;
    private long commentCount;

    public Post(long id, enum PostType type, long AcceptedAnswer, long userId,
                String userDisplayName, String title, long parentId,
                long score, String creationDate, List tags, long commentCount) {
        this.id = id;
        this.type = type;
        this.acceptedAnswer = acceptedAnswer;
        this.userId = userId;
        this.userDisplayName = userDisplayName;
        this.title = title;
        this.parentId = parentId;
        this.answers = new ArrayList<Long>();
        this.score = score;
        this.creationDate = Date.fromString(creationDate);
        this.tags = tags; // fazer clone
        this.comment_count = comment_count;
    }

    public long getId() {
        return this.id;
    }

    public enum PostType getType() {
        return this.type;
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

    public long getScore() {
        return this.score;
    }

    public List getAnswers() {
        return this.answers; // fazer clone
    }

    public void addAnswer(long id) {
        this.answers.add(id);
    }

    public Date getDate() {
        return this.date.clone();
    }

    public boolean hasTag(long tagId) {
        return this.tags.contains(tagId);
    }

    public List getTags() {
        return this.tags; // fazer clone
    }

    public long getCommentCount() {
        return this.commentCount;
    }

};

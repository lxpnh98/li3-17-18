package engine;

public enum PostType {
    QUESTION(1),
    ANSWER(2),
    OTHERS(3);

    private int value;

    private PostType (int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}

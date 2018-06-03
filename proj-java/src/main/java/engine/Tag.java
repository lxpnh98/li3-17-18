package engine;

public class Tag {

    private long id;
    private String name;

    public Tag() {
        this.id = 0;
        this.name = "";
    }

    public Tag(long id, String name) {
        this.id = id;
        this.name = name;
    }

    public Tag(Tag t) {
        this.id = t.getId();
        this.name = t.getName();
    }

    public long getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Tag clone() {
        return new Tag(this);
    }

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }
        if ((o == null) || (o.getClass() != this.getClass())) {
            return false;
        }
        Tag t = (Tag) o;
        return ((this.id == t.getId()) && (this.name.equals(t.getName())));
    }

    public String toString() {
        return "Tag =>\n Id: " + this.id + "\n Nome: " + this.name;
    }
}
package engine;

import java.util.ArrayList;
import java.lang.String;

/**
 * Write a description of class User here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class User {
    // Variáveis de instância
    private long id;
    private long rep;
    private String displayName;
    private String bio;
    private int postCount;

    /**
     * Constructor for objects of class User
     */
    public User() {
        this.id = 0;
        this.rep = 0;
        this.displayName = "";
        this.bio = "";
        this.postCount = 0;
    }

    public User(long id, long rep, String displayName, String bio, int postCount) {
        this.id = id;
        this.rep = rep;
        this.displayName = displayName;
        this.bio = bio;
        this.postCount = postCount;
    }

    public User(User u) {
        this.id = u.getId();
        this.rep = u.getRep();
        this.displayName = u.getDisplayName();
        this.bio = u.getBio();
        this.postCount = u.getPostCount();
    }

    public long getId() {
        return this.id;
    }

    public long getRep() {
        return this.rep;
    }

    public String getBio() {
        return this.bio;
    }

    public String getDisplayName() {
        return this.displayName;
    }

    public int getPostCount() {
        return this.postCount;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setRep(long rep) {
        this.rep = rep;
    }

    public void setBio(String bio) {
        this.bio = bio;
    }

    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    public void setPostCount(int postCount) {
        this.postCount = postCount;
    }

    public User clone() {
        return new User(this);
    }

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }
        if ((o == null) || (o.getClass() != this.getClass())) {
            return false;
        }
        User u = (User) o;
        return (this.id == u.getId()) && (this.rep == u.getRep()) &&
               (this.bio == u.getBio()) && (this.displayName == u.getDisplayName()) &&
               (this.postCount == u.getPostCount());
    }

    public String toString() {

        return " Utilizador =>\n Id: " + this.id + "\n Reputação: " + this.rep +
               "\n Bio: " + this.bio + "\n Nome de utilizador: " + this.displayName +
               "\n Número de posts: " + this.postCount;
    }
}

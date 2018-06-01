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
    private String display_name;
    private String bio;
    private ArrayList<Long> posts;
    private int post_count;

    /**
     * Constructor for objects of class User
     */
    public User() {
        this.id = 0;
        this.rep = 0;
        this.display_name = "";
        this.bio = "";
        this.post_count = 0;
        this.posts = new ArrayList<Long>();
    }

    public User(long id, long rep, String display_name, String bio, int post_count, ArrayList<Long> posts) {
        this.id = id;
        this.rep = rep;
        this.display_name = display_name;
        this.bio = bio;
        this.post_count = post_count;
        this.posts = posts;
    }

    public User(User umUser) {
        this.id = umUser.getId();
        this.rep = umUser.getRep();
        this.display_name = umUser.getDisplay_name();
        this.bio = umUser.getBio();
        this.post_count = umUser.getPost_count();
        this.posts = umUser.getPosts();
    }

    public long getId(){
        return this.id;
    }

    public long getRep(){
        return this.rep;
    }

    public String getBio(){
        return this.bio;
    }

    public String getDisplay_name(){
        return this.display_name;
    }

    public int getPost_count(){
        return this.post_count;
    }

    public ArrayList<Long> getPosts(){
        ArrayList<Long> clone_posts = new ArrayList<Long>();
        clone_posts.addAll(this.posts);

        return clone_posts;
    }

    public void setId(long id){
        this.id = id; 
    }

    public void setRep(long rep){
        this.rep = rep;
    }

    public void setBio(String bio){
        this.bio = bio;
    }

    public void setDisplay_name(String display_name){
        this.display_name = display_name;
    }

    public void setPost_count(int post_count){
        this.post_count = post_count;
    }

    public void setPosts(ArrayList<Long> new_posts){
        this.posts.removeAll(this.posts);
        this.posts.addAll(new_posts);
    }

    public boolean equals(Object o){
        if (o == this) return true;
        if ((o == null) || (o.getClass()!= this.getClass())) return false;
        User p = (User) o;
        return (this.id == p.getId()) && (this.rep == p.getRep()) && (this.bio == p.getBio()) && (this.display_name == p.getDisplay_name()) && (this.post_count == p.getPost_count()) && (this.posts.equals(p.getPosts()));
    }

    public String toSting(){

        String listString = "";

        for (long l : this.posts){
            listString += String.valueOf(l) + "\n";
        }

        return "Utilizador => Id: " + this.id + " Reputação: " + this.rep + " Bio: " + this.bio +  " Nome de utilizador: " + this.display_name + " Número de posts: " + this.post_count + " Lista de posts: " + listString;
    }
}

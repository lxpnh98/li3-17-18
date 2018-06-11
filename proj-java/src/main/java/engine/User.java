package engine;

import java.util.ArrayList;
import java.lang.String;

/**
 * Class User, onde se encontra toda a informação sobre o utilizador.
 * @author Alexandre Mendonça Pinho (A82441)
 *          Joel Filipe Esteves Gama (A82202)
 *          Tiago Martins Pinheiro (A82491)
 */
public class User {
    /** Id do utilizador */
    private long id;
    /** Reputação do utilizador */
    private long rep;
    /** Nome do utilizador */
    private String displayName;
    /** Biografia do utilizador */
    private String bio;
    /** Número de posts do utilizador*/
    private int postCount;

    /**
      * Construtor por omissão do User.
      */
    public User() {
        this.id = 0;
        this.rep = 0;
        this.displayName = "";
        this.bio = "";
        this.postCount = 0;
    }

    /**
      * Construtor parametrizado do User.
      */
    public User(long id, long rep, String displayName, String bio, int postCount) {
        this.id = id;
        this.rep = rep;
        this.displayName = displayName;
        this.bio = bio;
        this.postCount = postCount;
    }

    /**
      * Construtorde cópia do User.
      */
    public User(User u) {
        this.id = u.getId();
        this.rep = u.getRep();
        this.displayName = u.getDisplayName();
        this.bio = u.getBio();
        this.postCount = u.getPostCount();
    }

    /**
     * Devolve o id do utilizador.
     * @return long Id.
     */
    public long getId() {
        return this.id;
    }

    /**
     * Devolve a reputação do utilizador.
     * @return long Reputação.
     */
    public long getRep() {
        return this.rep;
    }

    /**
     * Devolve a biografia do utilizador.
     * @return String Biografia.
     */
    public String getBio() {
        return this.bio;
    }

    /**
     * Devolve o nome do utilizador.
     * @return String DisplayName.
     */
    public String getDisplayName() {
        return this.displayName;
    }

    /**
     * Devolve o número de posts do utilizador.
     * @return int PostCount.
     */
    public int getPostCount() {
        return this.postCount;
    }

    /**
     * Atualiza o id de um utilizador.
     * @param long id Novo id.
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Atualiza a reputação de um utilizador.
     * @param long rep Nova reputação.
     */
    public void setRep(long rep) {
        this.rep = rep;
    }

    /**
     * Atualiza a biografia de um utilizador.
     * @param String bio Nova biografia.
     */
    public void setBio(String bio) {
        this.bio = bio;
    }

    /**
     * Atualiza o nome de um utilizador.
     * @param String displayName Novo nome do utlizador.
     */
    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    /**
     * Atualiza o número de posts de um utilizador.
     * @param int postCount Novo número de posts.
     */
    public void setPostCount(int postCount) {
        this.postCount = postCount;
    }

    /**
     * Cria uma cópia do objecto User.
     * @return User
     */
    public User clone() {
        return new User(this);
    }

    /**
     * Verifica a igualdade de dois objectos.
     * @param o;
     * @return Valor boleano da comparação.
     */
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

    /**
     * Devolve toda a informação que contém o objeto User.
     * @return String informação do utilizador. 
     */
    public String toString() {

        return " Utilizador =>\n Id: " + this.id + "\n Reputação: " + this.rep +
               "\n Bio: " + this.bio + "\n Nome de utilizador: " + this.displayName +
               "\n Número de posts: " + this.postCount;
    }
}

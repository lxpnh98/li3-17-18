/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491)
 */

package engine;

/**
 * Class Tag, onde se encontra toda a informação sobre a Tag.
 */
public class Tag {

    /** Id da Tag */
    private long id;
    /** Nome da tag */
    private String name;

    /**
     * Construtor por omissão da Tag.
     */
    public Tag() {
        this.id = 0;
        this.name = "";
    }
    /**
     * Construtor parametrizado da Tag.
     */
    public Tag(long id, String name) {
        this.id = id;
        this.name = name;
    }

    /**
     * Construtorde cópia da Tag.
     */
    public Tag(Tag t) {
        this.id = t.getId();
        this.name = t.getName();
    }

    /**
     * Devolve o id da Tag.
     * @return long Id.
     */
    public long getId() {
        return this.id;
    }

    /**
     * Devolve o nome da Tag.
     * @return String nome.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Atualiza o id da Tag.
     * @param long Id.
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Atualiza o nome da Tag.
     * @param String nome.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Cria uma cópia do objecto Tag.
     * @return Tag
     */
    public Tag clone() {
        return new Tag(this);
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
        Tag t = (Tag) o;
        return ((this.id == t.getId()) && (this.name.equals(t.getName())));
    }

    /**
     * Devolve toda a informação que contém o objeto Tag.
     * @return String informação da tag. 
     */
    public String toString() {
        return "Tag =>\n Id: " + this.id + "\n Nome: " + this.name;
    }
}

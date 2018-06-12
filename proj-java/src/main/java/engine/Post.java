package engine;

import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;
import java.util.concurrent.ThreadLocalRandom;
import java.util.Set;
import java.util.HashSet;
import java.time.LocalDateTime;

/**
 * Class Post, onde se encontra toda a informação sobre o post.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491)
 */
public class Post {
    /** Id do Post */
    private long id;
    /** Id do user criador do Post */
    private long userId;
    /** Score do Post*/
    private long score;
    /** Número de comentários */
    private long commentCount;
    /** Data de Criação de um Post */
    private LocalDate creationDate;
    /** Tipo de Post: 1 - Question, 2 - Answer, 3 - Outros.*/
    private PostType type;
    /** Id da resposta aceite, no caso de ser uma pergunta.*/
    private long acceptedAnswer;
    /** Nome do utilizador, caso não tenha id. */
    private String userDisplayName;
    /** Título de um post.*/
    private String title;
    /** Set de ids das respostas de uma pergunta.*/
    private Set<Long> answers;
    /** Set de strings, cada string contendo uma tag de um Post.*/
    private Set<String> tags;
    /** Id da respetiva pergunta, no caso de ser uma resposta.*/
    private long parentId;

    /**
      * Construtor por omissão do Post.
      */
    public Post() {
        this.id = -1;
        this.userId = -1;
        this.score = -1;
        this.commentCount = -1;
        this.type = PostType.OTHERS;
        this.acceptedAnswer = -1;
        this.userDisplayName = "";
        this.title = "";
        this.answers = new HashSet<>();
        this.creationDate = Post.randomDate();
        this.tags = new HashSet<>();
        this.parentId = -1;
    }

    /**
      * Construtor parametrizado do Post.
      */
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
        this.answers = new HashSet<Long>();
        this.score = score;
        this.creationDate = creationDate;
        this.tags = tags; // fazer clone
        this.commentCount = commentCount;
    }

    /**
      * Construtorde cópia do Post.
      */
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
        this.answers = p.getAnswers();
    }

    /**
     * Devolve o id do Post.
     * @return long Id.
     */
    public long getId() {
        return this.id;
    }

    /**
     * Devolve o id do user criador do Post.
     * @return long User id.
     */
    public long getUserId() {
        return this.userId;
    }

    /**
     * Devolve o score do Post.
     * @return long Score.
     */
    public long getScore() {
        return this.score;
    }

    /**
     * Devolve o número de comentários de um determinado Post.
     * @return long Número de comentários.
     */
    public long getCommentCount() {
        return this.commentCount;
    }

    /**
     * Devolve a data de criação do Post.
     * @return LocalDate Data de criação.
     */
    public LocalDate getCreationDate() {
        return this.creationDate;
    }

    /**
     * Devolve o tipo do Post.
     * @return PostType Tipo (1 - Question, 2- Answer, 3 - Outros).
     */
    public PostType getType() {
        return this.type;
    }

    /**
     * Devolve o id da resposta aceite de uma pergunta.
     * @return long Id da resposta aceite.
     */
    public long getAcceptedAnswer() {
        return this.acceptedAnswer;
    }

    /**
     * Devolve o nome de um utilizador.
     * @return String nome de utilizador.
     */
    public String getUserDisplayName() {
        return this.userDisplayName;
    }

    /**
     * Devolve o título de um Post.
     * @return String título.
     */
    public String getTitle() {
        return this.title;
    }

    /**
     * Devolve o conjunto de tags de um Post.
     * @return Set<String> Conjunto de tags.
     */
    public Set<String> getTags() {
        return this.tags; // fazer clone
    }

    /**
     * Devolve o id da pergunta.
     * @return long ParentId.
     */
    public long getParentId() {
        return this.parentId;
    }

    /**
     * Devolve o conjunto de respostas de um Post.
     * @return Set<long> Ids das respostas.
     */
    public Set<Long> getAnswers() {
        return this.answers; // fazer clone
    }


    /**
     * Devolve o número de respostas de um Post.
     * @return int Número de respostas.
     */
    public int getNumAnswers() {
        return this.answers.size();
    }

    /**
     * Atualiza o id de um Post.
     * @param long Id.
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Atualiza o id do user criador do Post.
     * @param long UserId.
     */
    public void setUserId(long userId) {
        this.userId = userId;
    }

    /**
     * Atualiza o score de um Post.
     * @param long Score.
     */
    public void setScore(long score) {
        this.score = score;
    }

    /**
     * Atualiza o número de comentários de um Post.
     * @param long número de comentários.
     */
    public void setCommentCount(long commentCount) {
        this.commentCount = commentCount;
    }

    /**
     * Atualiza a data de criação de um Post.
     * @param LocalDate Data da criação.
     */
    public void setCreationDate(LocalDate d) {
        this.creationDate = d;
    }

    /**
     * Atualiza o tipo do Post.
     * @param PostType Tipo de post.
     */
    public void setType(PostType type) {
        this.type = type;
    }

    /**
     * Atualiza a resposta aceite do Post.
     * @param long Resposta aceite.
     */
    public void setAcceptedAnswer(long acceptedAnswer) {
        this.acceptedAnswer = acceptedAnswer;
    }

    /**
     * Atualiza o nome de utilizador do criador do Post.
     * @param String Nome de utilizador.
     */
    public void setUserDisplayName(String userDisplayName) {
        this.userDisplayName = userDisplayName;
    }

    /**
     * Atualiza o título do Post.
     * @param String Título.
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * Atualiza o Set das tags do Post.
     * @param Set<String> String das tags.
     */
    public void setTags(Set<String> tags) {
        for(String s : tags) {
            this.tags.add(s);
        }
    }

    /**
     * Atualiza o id do pai de um certo Post.
     * @param long Id do post pai.
     */
    public void setParentId(long parentId) {
        this.parentId = parentId;
    }

    /**
     * Adiciona o id de uma reposta ao Set.
     * @param long Id da reposta.
     */
    public void addAnswer(long id) {
        this.answers.add(id);
    }
    
    /**
      * Metódo que cria uma data aleatória.
      * @return LocalDate Data aleatória.
      */ 
    public static LocalDate randomDate() { // temporário, só para testar enquanto não se tem datas
        long minDay = LocalDate.MIN.toEpochDay();
        long maxDay = LocalDate.MAX.toEpochDay();
        long randomDay = ThreadLocalRandom.current().nextLong(minDay, maxDay);
        return LocalDate.ofEpochDay(randomDay);
    }

    /**
     * Testa se o post contém uma determinada tag.
     * @param String Tag a encontrar.
     * @retun boolean True caso contenha, false caso contrário.
     */
    public boolean hasTag(String name) {
        return this.tags.contains(name);
    }

    /**
     * Cria uma cópia do objecto Post.
     * @return Post
     */
    public Post clone() {
        return new Post(this);
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
        Post p = (Post) o;
        return (this.id == p.getId() && this.userId == p.getUserId() && 
            this.score == p.getScore() && this.commentCount == p.getCommentCount() &&
            this.creationDate.equals(p.getCreationDate()) && this.type.equals(p.getType()) &&
            this.acceptedAnswer == p.getAcceptedAnswer() && this.userDisplayName.equals(p.getUserDisplayName()) &&
            this.title.equals(p.getTitle()) && this.tags.equals(p.getTags()) &&
            this.parentId == p.getParentId() && this.answers.equals(p.getAnswers()));       
    }

    /**
     * Devolve toda a informação que contém o objeto Post.
     * @return String informação do post. 
     */
    public String toString() {
        return "\nPost =>\n Id: " + this.id + "\n UserId: " + this.userId +
               "\n Score: " + this.score + "\n Número de comentários: " + this.commentCount +
               "\n Data de criação: " + this.creationDate + "\n Tipo: " + this.type +
               "\n Resposta aceite: " + this.acceptedAnswer + "\n Nome do utilizador: " + this.userDisplayName +
               "\n Título: " + this.title + "\n Tags: " + this.tags + 
               "\n ParentId: " + this.parentId + "\n Respostas: " + this.answers;
    }
}
/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491)
 */

package engine;

import common.MyLog;
import common.Pair;
import li3.TADCommunity;
import org.xml.sax.SAXException;

import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Set;
import java.util.TreeSet;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.Comparator;
import java.util.Iterator;
import java.util.stream.Collectors;
import java.util.Collections;

/**
 * Comparador de posts por data (ordem crescente).
 */
class PostsByDateComparator implements Comparator<Post> {
    /**
     * Método que compara os dois posts por data.
     * Para diferenciar posts com a mesma data, compara também os seus ids.
     * @param p1 Primeiro post.
     * @param p2 Segundo post.
     * @return   Resultado da comparação.
     */
    public int compare(Post p1, Post p2) {
        int dateCmp = p1.getCreationDate().compareTo(p2.getCreationDate());
        if (dateCmp == 0) {
            return new Long(p1.getId()).compareTo(p2.getId());
        }
        return dateCmp;
    }
}

/**
 * Comparador de posts por data (ordem crescente), a partir dos seus ids.
 */
class PostIdsByDateComparator implements Comparator<Long> {
    private TCDExample community;

    /**
     * Método que guarda referência à estrutura de dados principal, para ter acesso à informação necessária.
     * @param c Referência à estrutura de dados.
     */
    public void setCommunity(TCDExample c) {
        this.community = c;
    }

    /**
     * Método que compara os dois posts por data, a partir dos seus ids.
     * Para diferenciar posts com a mesma data, compara também os seus ids.
     * @param id1 Id do primeiro post.
     * @param id2 Id do segundo post.
     * @return   Resultado da comparação.
     */
    public int compare(Long id1, Long id2) {
        int dateCmp = this.community.getPost(id1).getCreationDate().compareTo(this.community.getPost(id2).getCreationDate());
        if (dateCmp == 0) {
            return id1.compareTo(id2);
        }
        return dateCmp;
    }
}

/**
 * Comparador de users por reputação (ordem crescente), a partir dos seus ids.
 */
class UsersByRepComparator implements Comparator<Long> {
    private TCDExample community;

    /**
     * Método que guarda referência à estrutura de dados principal, para ter acesso à informação necessária.
     * @param c Referência à estrutura de dados.
     */
    public void setCommunity(TCDExample c) {
        this.community = c;
    }

    /**
     * Método que compara os dois users por reputação, a partir dos seus ids.
     * Para diferenciar users com a mesma reputação, compara também os seus ids.
     * @param id1 Id do primeiro user.
     * @param id2 Id do segundo user.
     * @return   Resultado da comparação.
     */
    public int compare(Long id1, Long id2) {
        int repCmp = (new Long(this.community.getUser(id1).getRep())).compareTo(this.community.getUser(id2).getRep());
        if (repCmp == 0) {
            return (new Long(this.community.getUser(id1).getId())).compareTo(this.community.getUser(id2).getId());
        }
        return repCmp;
    }
}

/**
 * Comparador de users por número de posts (ordem decrescente), a partir dos seus ids.
 */
class UsersByNumberOfPostsComparator implements Comparator<Long> {
    private TCDExample community;

    /**
     * Método que guarda referência à estrutura de dados principal, para ter acesso à informação necessária.
     * @param c Referência à estrutura de dados.
     */
    public void setCommunity(TCDExample c) {
        this.community = c;
    }

    /**
     * Método que compara os dois users pelo seu número de posts, a partir dos seus ids.
     * Para diferenciar users com o mesmo número de posts, compara também os seus ids.
     * @param id1 Id do primeiro user.
     * @param id2 Id do segundo user.
     * @return   Resultado da comparação.
     */
    public int compare(Long id1, Long id2) {
        int return1 = (new Integer(this.community.getUser(id2).getPostCount())).compareTo(this.community.getUser(id1).getPostCount());
        if (return1 == 0) {
            return (new Long(this.community.getUser(id2).getId())).compareTo(this.community.getUser(id1).getId());
        }
        return return1;
    }
}

/**
 * Classe da estrutura de dados principal, e onde são disponibilizados os métodos de resposta às queries.
 */
public class TCDExample implements TADCommunity {

    /** Ficheiro de log. */
    private MyLog qelog;
    /** Map de ids de posts para posts */
    private Map<Long, Post> posts;
    /** Map de ids de users para users */
    private Map<Long, User> users;
    /** Map de nomes de tags para tags */
    private Map<String, Tag> tags;
    /** Set de posts ordenados cronologicamente */
    private TreeSet<Post> postsByDate;
    /** Map de ids de users para o set ordenado cronologicamente dos ids dos seus posts */
    private Map<Long, TreeSet<Long>> postsByUser;
    /** Set de users ordenados por reputação */
    private TreeSet<Long> usersByRep;
    /** Set de users ordenados pelo número de posts */
    private TreeSet<Long> usersByPosts;

    /**
     * Método que inicializa as estruturas de dados.
     */
    public void init() {
        this.qelog = new MyLog("queryengine");
        this.posts = new HashMap<Long, Post>();
        this.users = new HashMap<Long, User>();
        this.tags = new HashMap<String, Tag>();
        this.postsByDate = new TreeSet<Post>(new PostsByDateComparator());
        this.postsByUser = new HashMap<Long, TreeSet<Long>>();
        UsersByRepComparator cmp = new UsersByRepComparator();
        cmp.setCommunity(this);
        this.usersByRep = new TreeSet<Long>(cmp);
        UsersByNumberOfPostsComparator u = new UsersByNumberOfPostsComparator();
        u.setCommunity(this);
        this.usersByPosts = new TreeSet<Long>(u);

    }

    /**
     * Método que adiciona um post à estrutura de dados.
     * @param p Post a adicionar.
     * @param addedBeforeParent Lista de posts cujo id é inferior ao respetivo post parente, e logo são adicionados antes dele.
     */
    public void addPost(Post p, List<Long> addedBeforeParent) {
        Post newPost = p.clone();
        this.posts.put(p.getId(), newPost);
        this.postsByDate.add(newPost);

        // Atualizar PostCount e usersByPosts
        long userId = p.getUserId();
        this.usersByPosts.remove(userId);

        Post parent = this.posts.get(p.getParentId());
        if (parent != null) {
            parent.addAnswer(p.getId());
        } else if (p.getParentId() > p.getId()) {
            addedBeforeParent.add(p.getId());
        }

        int postCount = this.users.get(p.getUserId()).getPostCount();
        this.users.get(p.getUserId()).setPostCount(postCount + 1);

        this.usersByPosts.add(userId);

        TreeSet<Long> posts = this.postsByUser.get(p.getUserId());
        if (posts == null) {
            PostIdsByDateComparator c = new PostIdsByDateComparator();
            c.setCommunity(this);
            posts = new TreeSet<Long>(c);
        }
        posts.add(p.getId());
        this.postsByUser.put(p.getUserId(), posts);
    }

    /**
     * Método que adiciona um user à estrutura de dados.
     * @param u User a adicionar.
     */
    public void addUser(User u) {
        User newUser = u.clone();
        this.users.put(u.getId(), newUser);
        this.usersByRep.add(newUser.getId());
        this.usersByPosts.add(newUser.getId());
    }

    /**
     * Método que adiciona um user à estrutura de dados.
     * @param t Tag a adicionar.
     */
    public void addTag(Tag t) {
        this.tags.put(t.getName(), t.clone());
    }

    /**
     * Método que devolve um post dado o seu id.
     * @param id Id do post.
     * @return   Post com o id igual.
     */
    public Post getPost(long id) {
        return this.posts.get(id).clone();
    }

    /**
     * Método que devolve um user dado o seu id.
     * @param id Id do user.
     * @return   User com o id igual.
     */
    public User getUser(long id) {
        return this.users.get(id).clone();
    }

    /**
     * Método que devolve um user dado o seu nome.
     * @param name Nome da tag.
     * @return     Tag com o nome igual.
     */
    public Tag getTag(String name) {
        return this.tags.get(name);
    }

    /**
     * Método que devolve a lista de posts entre duas datas.
     * @param begin Data inicial.
     * @param end   Data final.
     * @return      List de posts entre a data inicial e a data final, inclusive.
     */
    public List<Post> getPostsBetween(LocalDate begin, LocalDate end) {
        Post beginPost = new Post();
        beginPost.setCreationDate(begin.plusDays(0L));
        Post endPost = new Post();
        endPost.setCreationDate(end.plusDays(0L));
        Iterator<Post> it = this.postsByDate.subSet(beginPost, true, endPost, true).descendingIterator();
        List<Post> r = new ArrayList();
        while (it.hasNext()) {
            r.add(it.next().clone());
        }
        return r;
    }

    /**
     * Método que devolve os utilizadores ordenados por reputação.
     * @return Lista dos ids dos users por ordem crescente de reputação.
     */
    public List<Long> getUsersByRep() {
        return this.usersByRep.stream().collect(Collectors.toList());
    }

    /**
     * Método que devolve os posts de um utilizador.
     * @param id Id do utilizador.
     * @return Lista dos ids dos posts do utilizador especificado, por ordem cronológica.
     */
    public List<Long> getPostIdsBy(long id) {
        return this.postsByUser.get(id).stream().collect(Collectors.toList());
    }

    /**
     * Método que devolve os utilizadores ordenados pelo número de posts.
     * @return Lista dos ids dos users por ordem decrescente do número de posts.
     */
    public List<Long> getUsersByPosts() {
        return this.usersByPosts.stream().collect(Collectors.toList());
    }

    /**
     * Método que devolve as perguntas que contêm uma palavra no seu título, por ordem cronológica inversa.
     * @param word Palavra que tem de ocorrer no título dos posts.
     * @return Lista dos ids dos posts que contêm a palavra, por ordem cronológica inversa.
     */
    public List<Long> getPostsByDate(String word) {
        List<Long> posts = this.postsByDate.stream().filter(p -> p.getType().equals(PostType.QUESTION) && p.getTitle().contains(word))
                               .map(Post::getId).collect(Collectors.toList());
        Collections.reverse(posts);
        return posts;
    }

    /**
     * Método que devolve a reputação de um utilizador dado o seu id.
     * @param id Id do utilizador.
     * @return   Reputação do utilizador.
     */
    public long getUserRep(long id) {
        User u = this.getUser(id);
        long res = u.getRep();
        return res;
    }

    /**
     * Método que carrega o conteúdo de um dump de uma comunidade do StackExchange.
     * @param dumpPath Path para a diretoria onde se encontram os ficheiros xml.
     */
    public void load(String dumpPath) {
        this.init();
        List<Long> addedBeforeParent = new LinkedList<>();
        Load.load(this, dumpPath, addedBeforeParent);
        this.addToParents(addedBeforeParent);
    }

    /**
     * Método que, para cada post cujo pai ainda não tinha sido adicionado, adiciona como resposta ao seu pai.
     * @param addedBeforeParent Lista dos ids dos posts que foram adicionados à estrutura antes dos respetivos pais.
     */
    private void addToParents(List<Long> addedBeforeParent) {
        addedBeforeParent.forEach(id -> {
            long parentId = this.posts.get(id).getParentId();
            Post parent = this.posts.get(parentId);
            if (parent != null) {
                parent.addAnswer(id);
            } else {
                qelog.writeLog("Parent post with id " + parentId + " not added.");
            }
        });
    }

    /**
     *  Método que implementa a query 1: Dado o identificador de um post, a função deve retor-
     * nar o título do post e o nome de utilizador do autor. Se o post
     * for uma resposta, a função deverá retornar informações (tı́tulo e utilizador)
     * da pergunta correspondente.
     * @param id Id do post.
     * @return Par (título do post, nome de utilizador do autor)
     */
    public Pair<String,String> infoFromPost(long id) {
        Pair<String,String> res = QueryOne.resposta(this, id);
        return res;
    }

    /**
     *  Método que implementa a query 2: Pretende obter o top N utilizadores com maior número
     * de posts de sempre. Para isto, devem ser considerados tanto perguntas
     * quanto respostas dadas pelo respectivo utilizador.
     * @param N Número de utilizadores a listar.
     * @return Lista dos id dos N utilizadores com o maior número de posts.
     */
    public List<Long> topMostActive(int N) {
        List<Long> res = QueryTwo.resposta(this, N);
        return res;
    }

    /**
     *  Método que implementa a query 3: Dado um intervalo de tempo arbitrário, obter o número
     * total de posts (identificando perguntas e respostas separadamente) neste
     * perı́odo;
     * @param begin Data inicial.
     * @param end   Data final.
     * @return      Par (número de perguntas, número de respostas)
     */
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
          Pair pair = QueryThree.answersquestions(this, begin, end);
          return pair;
    }

    /**
     *  Método que implementa a query 4: Dado um intervalo de tempo arbitrário, retornar todas
     * as perguntas contendo uma determinada tag. O retorno da função deverá ser
     * uma lista com os IDs das perguntas ordenadas em cronologia inversa.
     * @param tag   Nome da tag.
     * @param begin Data inicial.
     * @param end   Data final.
     * @return      List dos ids das perguntas com a tag.
     */
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        List<Long> res = QueryFour.resposta(this, tag, begin, end);
        return res;
    }

    /**
     *  Método que implementa a query 5: Dado um ID de utilizador, devolver a informação do
     * seu perfil (short bio) e os IDs dos seus 10 últimos posts (perguntas ou res-
     * postas), ordenados por cronologia inversa.
     * @param id Id do utilizador.
     * @return   Par (short bio, lista dos ids dos 10 últimos posts)
     */
    public Pair<String, List<Long>> getUserInfo(long id) {
        Pair<String, List<Long>> res = QueryFive.resposta(this, id);
        return res;
    }

    /**
     *  Método que implementa a query 6: Dado um intervalo de tempo arbitrário, devolver os
     * IDs das N respostas com mais votos, em ordem decrescente do número de votos.
     * @param N     Número de respostas a incluir no resultado
     * @param begin Data inicial.
     * @param end   Data final.
     * @return      Lista dos ids das N respostas com mais votos entre as duas datas.
     */
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        List<Long> posts = QuerySix.resposta(this, N, begin, end);
        return posts;
    }

    /**
     *  Método que implementa a query 7: Dado um intervalo de tempo arbitrário, devolver as
     * IDs das N perguntas com mais respostas, em ordem decrescente do número de respostas.
     * @param N     Número de perguntas a incluir no resultado.
     * @param begin Data inicial.
     * @param end   Data final.
     * @return      List dos ids das N perguntas com mais respostas.
     */
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        List<Long> res = QuerySeven.resposta(this, N, begin, end);
        return res;
    }

    /**
     *  Método que implementa a query 8: Dado uma palavra, devolver uma lista com os IDs de
     * N perguntas cujos tı́tulos a contenham, ordenados por cronologia inversa.
     * @param N    Número de perguntas a incluir no resultado.
     * @param word Palavra a procurar.
     * @return     Lista dos ids das N perguntas contendo a palavra.
     */
    public List<Long> containsWord(int N, String word) {
        List<Long> res = QueryEight.resposta(this, N, word);
        return res;
    }

    /**
     *  Método que implementa a query 9: Dados os IDs de dois utilizadores, devolver as últimas
     * N perguntas (cronologia inversa) em que participaram dois utilizadores especı́ficos.
     * Note que os utilizadores podem ter participado via pergunta ou respostas.
     * @param N   Número de perguntas a incluir no resultado.
     * @param id1 Id do primeiro utilizador.
     * @param id2 Id do segundo utilizador.
     * @return    Lista das últimas N perguntas que em os dois utilizadores participam.
     */
    public List<Long> bothParticipated(int N, long id1, long id2) {
        List<Long> res = QueryNine.resposta(this, N, id1, id2);
        return res;
    }

    /**
     *  Método que implementa a query 10: Dado o ID de uma pergunta, obter a melhor resposta.
     * @param id Id da pergunta
     * @return   Id da melhor resposta.
     */
    public long betterAnswer(long id) {
        long res = QueryTen.resposta(this,id);
        return res;
    }

    /**
     *  Método que implementa a query 11: Dado um intervalo arbitrário de tempo, devolver os
     * identificadores das N tags mais usadas pelos N utilizadores com melhor reputação.
     * Em ordem decrescente do número de vezes em que a tag foi usada.
     * @param N     Número de tags a incluir na resposta, a partir dos N utilizadores com melhor reputação.
     * @param begin Data inicial.
     * @param end   Data final.
     * @return      Lista dos ids das N tags mais utilizadas pelos N
     *              utilizadores com melhor reputação no intervalo de tempo.
     */
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        List<Long> res = QueryEleven.resposta(this, N, begin, end);
        return res;
    }

    /**
     * Método que limpa o estado da aplicação.
     */
    public void clear() {
    }
}

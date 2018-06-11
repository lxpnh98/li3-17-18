package engine;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.time.LocalDate;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * Classe responsável por fazer o parsing dos posts.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491)
 */
public class PostsParse extends DefaultHandler {

    /** Estrutura de dados principal */
    private TCDExample community;
    /** Lista onde serão guardados dos id dos posts cujos pai ainda não foram processados. */
    private List<Long> addedBeforeParent;

    /**
     * Construtor da classe, necessário para guardar referências às estruturas de dados que a classe altera.
     * @param c                  Estrutura de dados à qual é adicionada a informação.
     * @param addedBeforeParent  Lista onde serão guardados dos id dos posts cujos pai ainda não foram processados.
     */
    public PostsParse(TCDExample c, List<Long> addedBeforeParent) {
        super();
        this.community = c;
        this.addedBeforeParent = addedBeforeParent;
    }

    /**
     * Método que carrega a informação de um post para a estrutura de dados principal.
     * @param uri        O URI do namespace, ou vazio se não existir
     * @param localName  O nome local
     * @param qName      O nome com prefixo
     * @param attributes Os atributos do elemento
     */
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException {

        if ("row".equalsIgnoreCase(qName)) {
            Post post = new Post();

            // Set id
            String id = attributes.getValue("Id");
            post.setId(Long.parseLong(id));

            // Set userId
            String userId = attributes.getValue("OwnerUserId");
            post.setUserId(Long.parseLong(userId));

            // Set score
            String score = attributes.getValue("Score");
            post.setScore(Long.parseLong(score));

            // Set commentCount
            String commentCount = attributes.getValue("CommentCount");
            post.setCommentCount(Long.parseLong(commentCount));

            // Set date
            CharSequence creationDate = attributes.getValue("CreationDate");
            CharSequence dataParse = creationDate.subSequence(0,10);
            LocalDate date = LocalDate.parse(dataParse);
            post.setCreationDate(date);

            // Set PostType
            int postType = Integer.parseInt(attributes.getValue("PostTypeId"));
            if (postType == 1) {
                // Question
	            post.setType(PostType.QUESTION);

                // Set id acceptedAnswer
                String acceptedAnswer = attributes.getValue("AcceptedAnswerId");
                if (acceptedAnswer != null) {
                    post.setAcceptedAnswer(Long.parseLong(acceptedAnswer));
                }

                // Set userDisplayName
                String userDisplayName = attributes.getValue("OwnerDisplayName");
                post.setUserDisplayName(userDisplayName);

                // Set Title
                String title = attributes.getValue("Title");
                post.setTitle(title);

                // Set Tags
                String tags = attributes.getValue("Tags");
                // Tira marca inicial e final
                StringBuilder sb = new StringBuilder(tags);
                sb.deleteCharAt(0);
                sb.deleteCharAt(sb.length() - 1);
                String tagsSemMarcas = sb.toString();
                // Faz split das tags
                String tagsSep[] = tagsSemMarcas.split("><");
                // Copia para arrayList
                Set<String> tagSet = new HashSet<String>();
                for(int i = 0; i < tagsSep.length && tagsSep != null; i++) {
                	tagSet.add(tagsSep[i]);
                }
                post.setTags(tagSet);
            } else if (postType == 2) {
               post.setType(PostType.ANSWER);
               // Set ParentID
               String parentID = attributes.getValue("ParentId");
               post.setParentId(Long.parseLong(parentID));
            } else {
               post.setType(PostType.OTHERS);
            }
            if(post.getType() != PostType.OTHERS) {
                this.community.addPost(post, this.addedBeforeParent);
            }
        }
    }
}

package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * Classe responsável por fazer o parsing dos users.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491)
 */
public class UsersParse extends DefaultHandler {

    /** Estrutura de dados principal */
    private TCDExample community;

    /**
     * Construtor da classe, necessário para guardar referências às estruturas de dados que a classe altera.
     * @param c Estrutura de dados à qual é adicionada a informação.
     */
    public UsersParse(TCDExample c) {
        super();
        this.community = c;
    }

    /**
     * Método que carrega a informação de um user para a estrutura de dados principal.
     * @param uri        O URI do namespace, ou vazio se não existir
     * @param localName  O nome local
     * @param qName      O nome com prefixo
     * @param attributes Os atributos do elemento
     */
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException {

        if ("row".equalsIgnoreCase(qName)) {
            User user = new User();

            // Set Id
            String id = attributes.getValue("Id");
            user.setId(Long.parseLong(id));

            //Set Rep
            String rep = attributes.getValue("Reputation");
            user.setRep(Long.parseLong(rep));

            //Set Name
            String name = attributes.getValue("DisplayName");
            user.setDisplayName(name);

            //Set Bio
            String bio = attributes.getValue("AboutMe");
            user.setBio(bio);
            
            if (user.getId() != -1) {
                this.community.addUser(user);
            }
        }
    }
}

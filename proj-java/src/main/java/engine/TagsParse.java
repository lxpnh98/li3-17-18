package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * Classe responsável por fazer o parsing das tags.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491)
 */
public class TagsParse extends DefaultHandler {

    /** Estrutura de dados principal */
    private TCDExample community;

    /**
     * Construtor da classe, necessário para guardar referências às estruturas de dados que a classe altera.
     * @param c Estrutura de dados à qual é adicionada a informação.
     */
    public TagsParse(TCDExample c) {
        super();
        this.community = c;
    }

    /**
     * Método que carrega a informação de uma tag para a estrutura de dados principal.
     * @param uri        O URI do namespace, ou vazio se não existir
     * @param localName  O nome local
     * @param qName      O nome com prefixo
     * @param attributes Os atributos do elemento
     */
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException {

        if ("row".equalsIgnoreCase(qName)) {
            Tag tag = new Tag();

            // Set id
            String id = attributes.getValue("Id");
            tag.setId(Long.parseLong(id));

            // Set name
            String name = attributes.getValue("TagName");
            tag.setName(name);

            this.community.addTag(tag);
        }
    }
}

package engine;

import org.xml.sax.SAXException;

import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;

/**
 * Classe responsável por fazer o parsing de todos os ficheiros do dump.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82481)
 */
public class Load {

    /**
     * Método que carrega a informação necessária dos ficheiros para a estrutura de dados principal.
     * @param c                  Estrutura de dados à qual é adicionada a informação.
     * @param dumpPath           Diretoria onde estão os ficheiros do dump
     * @param addedBeforeParent  Lista onde serão guardados dos id dos posts cujos pai ainda não foram processados.
     */
    public static void load(TCDExample c, String dumpPath, List<Long> addedBeforeParent) {
        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();

        try {

            // Load/Parse dos Users
            SAXParser parserUser = saxParserFactory.newSAXParser();
            UsersParse usersHandler = new UsersParse(c);
            parserUser.parse(new File(dumpPath + "Users.xml"), usersHandler);

            // Load/Parse dos Posts
            SAXParser parserPost = saxParserFactory.newSAXParser();
            PostsParse postsHandler = new PostsParse(c, addedBeforeParent);
            parserPost.parse(new File(dumpPath + "Posts.xml"), postsHandler);

            // Load/Parse das Tags
            SAXParser parserTag = saxParserFactory.newSAXParser();
            TagsParse tagsHandler = new TagsParse(c);
            parserTag.parse(new File(dumpPath + "Tags.xml"), tagsHandler);

        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
    }

}

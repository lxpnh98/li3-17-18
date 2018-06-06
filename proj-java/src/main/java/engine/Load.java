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

public class Load {

    public static void load(TCDExample c, String dumpPath) {
        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();

        try {

            // Load/Parse dos Posts
            SAXParser parserPost = saxParserFactory.newSAXParser();
            PostsParse postsHandler = new PostsParse(c);
            parserPost.parse(new File(dumpPath + "Posts.xml"), postsHandler);

            // Load/Parse dos Users
            SAXParser parserUser = saxParserFactory.newSAXParser();
            UsersParse usersHandler = new UsersParse(c);
            parserUser.parse(new File(dumpPath + "Users.xml"), usersHandler);

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

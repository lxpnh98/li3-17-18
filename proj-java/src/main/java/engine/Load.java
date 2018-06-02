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
    
    public static void load(String dumpPath) {
        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();

        try {

            SAXParser parser = saxParserFactory.newSAXParser();
            postsParse handler = new postsParse();
            parser.parse(new File(dumpPath + "Posts.xml"), handler);

            List<Post> postList = handler.getPostList();

        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
    }

}
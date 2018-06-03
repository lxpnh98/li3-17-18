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

    public static void load(String dumpPath, List<Post> postList,
    	                     List<User> userList, List<Tag> tagList) {
        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();

        try {

        	// Load/Parse dos Posts
            SAXParser parserPost = saxParserFactory.newSAXParser();
            PostsParse postsHandler = new PostsParse();
            parserPost.parse(new File(dumpPath + "Posts.xml"), postsHandler);

            for(Post p : postsHandler.getPostList()) {
            	postList.add(p.clone());
            }

        	// Load/Parse dos Users
            SAXParser parserUser = saxParserFactory.newSAXParser();
            UsersParse usersHandler = new UsersParse();
            parserUser.parse(new File(dumpPath + "Users.xml"), usersHandler);

            for(User u : usersHandler.getUserList()) {
            	userList.add(u.clone());
            }

        	// Load/Parse das Tags
            SAXParser parserTag = saxParserFactory.newSAXParser();
            TagsParse tagsHandler = new TagsParse();
            parserTag.parse(new File(dumpPath + "Tags.xml"), tagsHandler);

            for(Tag t : tagsHandler.getTagList()) {
            	tagList.add(t.clone());
            }

        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
    }

}
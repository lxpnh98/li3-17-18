package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class PostsParse extends DefaultHandler {

    // List to hold Posts
    private List<Post> postList = null;
    private Post post = null;

    public List<Post> getPostList() {
        return this.postList;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException {
        
        if ("row".equalsIgnoreCase(qName)) {
            post = new Post();

            // SET COMUNS A TODOS OS POSTS
            // Set id
            String id = attributes.getValue("Id");
            post.setId(Long.parseLong(id));
            System.out.println("PostID: " + post.getId());

            // Set userId;
            String userId = attributes.getValue("OwnerUserId");
            post.setUserId(Long.parseLong(userId));
            System.out.println("UserID: " + post.getUserId());


            // Set PostType
            int postType = Integer.parseInt(attributes.getValue("PostTypeId"));
            if (postType == 1) {
                post.setType(PostType.QUESTION);

                // Question
                // Set id acceptedAnswer
                String acceptedAnswer = attributes.getValue("AcceptedAnswerId");
                if (acceptedAnswer != null) {
                    post.setAcceptedAnswer(Long.parseLong(acceptedAnswer));
                    System.out.println("AcceptedAnswer: " + post.getAcceptedAnswer());
                }

                // Set Title
                String title = attributes.getValue("Title");
                post.setTitle(title);
                System.out.println("Title: " + post.getTitle());

            } else if (postType == 2) {
               post.setType(PostType.ANSWER);
                // TODO: aqui vao ficar os sets que apenas as respostas tem
            


            } else {
               // post.setType(PostType.OTHERS);
            }

            if (postList == null) {
                postList = new ArrayList<>();
                postList.add(post);
            } else {
                postList.add(post);
            } 
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("posts")) {
            postList.add(post);
        }
    }
}
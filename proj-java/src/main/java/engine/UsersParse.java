package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class UsersParse extends DefaultHandler {

    private List<User> userList = null;
    private User user = null;

    public List<User> getUserList() {
        return this.userList;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException {
        
        if ("row".equalsIgnoreCase(qName)) {
            user = new User();

            // Set Id
            String id = attributes.getValue("Id");
            user.setId(Long.parseLong(id));
            // System.out.println("UserID: " + user.getId());

            //Set Rep
            String rep = attributes.getValue("Reputation");
            user.setRep(Long.parseLong(rep));
            //System.out.println("Reputação: " + user.getRep());

            //Set Name
            String name = attributes.getValue("DisplayName");
            user.setDisplayName(name);
            //System.out.println("Nome: " + user.getDisplayName());

            //Set Bio
            String bio = attributes.getValue("AboutMe");
            user.setBio(bio);
            //System.out.println("\nBio: " + user.getBio());

            if (userList == null) {
                userList = new ArrayList<>();
                userList.add(user);
            } else {
                userList.add(user);
            } 
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("users")) {
            userList.add(user);
        }
    }
}
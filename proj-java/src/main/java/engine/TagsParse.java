package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class TagsParse extends DefaultHandler {

    // List to hold Tags
    private List<Tag> tagList = null;
    private Tag tag = null;

    public List<Tag> getTagList() {
        return this.tagList;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException {
        
        if ("row".equalsIgnoreCase(qName)) {
            tag = new Tag();

            // Set id
            String id = attributes.getValue("Id");
            tag.setId(Long.parseLong(id));
            System.out.println("TagID: " + tag.getId());

            if (tagList == null) {
                tagList = new ArrayList<>();
                tagList.add(tag);
            } else {
                tagList.add(tag);
            } 
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("tags")) {
            tagList.add(tag);
        }
    }
}
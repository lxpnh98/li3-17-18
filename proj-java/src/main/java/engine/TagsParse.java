package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class TagsParse extends DefaultHandler {

    private TCDExample community;

    public TagsParse(TCDExample c) {
        super();
        this.community = c;
    }

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

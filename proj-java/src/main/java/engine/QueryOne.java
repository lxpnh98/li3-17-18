package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;
import common.Pair;
import li3.TADCommunity;

public class QueryOne {
    public static Pair<String,String> resposta(TCDExample c, long id){
        String titulo = "";
        String nome = "";
        Post p = c.getPost(id);
        if (p != null) {
            titulo = p.getTitle();
            nome = c.getUser(p.getUserId()).getDisplayName();
        }
        return new Pair<String,String>(titulo, nome);
    }
}

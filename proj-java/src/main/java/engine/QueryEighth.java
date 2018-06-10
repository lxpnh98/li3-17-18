package engine;

import java.util.ArrayList;
import java.util.List;
import common.Pair;
import li3.TADCommunity;

public class QueryEighth {
    public static List<Long> resposta(TCDExample c, int N, String word) {
        int i = 0;
        List<Long> res = new ArrayList<Long>();
        List<Post> posts = c.getPostsByDate();
        for(Post p : posts) {
            if(i < N) {
                if (p.getTitle().contains(word)) {
                    res.add(p.getId());
                    i++;
                }
            } else {
                break;
            }
        }
        return res;
    }
}
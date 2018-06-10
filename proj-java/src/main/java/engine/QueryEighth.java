package engine;

import java.util.ArrayList;
import java.util.List;
import common.Pair;
import li3.TADCommunity;

public class QueryEighth {
    public static List<Long> resposta(TCDExample c, int N, String word) {
        List<Long> res = c.getPostsByDate(word);
        return res.subList(0,N);
   	}
}
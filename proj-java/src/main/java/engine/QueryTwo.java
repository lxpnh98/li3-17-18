package engine;

import java.util.ArrayList;
import java.util.List;
import common.Pair;
import li3.TADCommunity;

public class QueryTwo {
    public static List<Long> resposta(TCDExample c, int N) {
        List<Long> res = c.getUsersByPosts();
        return res.subList(0,N);
    }
}
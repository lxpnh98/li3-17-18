package engine;

import java.util.List;
import java.util.Collections;
import java.time.LocalDate;
import java.util.stream.Collectors;
import common.Pair;
import li3.TADCommunity;

public class QueryFive {
    public static Pair<String, List<Long>> resposta(TCDExample c, long id) {
        User u = c.getUser(id);
        List<Long> l = c.getPostIdsBy(id);
        l = l.subList(Math.max(l.size() - 10, 0), l.size());
        Collections.reverse(l);
        return new Pair<String, List<Long>>(u.getBio(), l);
    }
}

package engine;

import java.util.List;
import java.util.Collections;
import java.time.LocalDate;
import java.util.stream.Collectors;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QueryFive.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491
 */
public class QueryFive {
    /**
     * Método que responde à query 5.
     * @param TCDExample c Estrutura de dados principal.
     * @param long Id do user.
     * @return Pair (Short-bio do user, Ids dos seus últimos 10 posts).
     */
    public static Pair<String, List<Long>> resposta(TCDExample c, long id) {
        User u = c.getUser(id);
        List<Long> l = c.getPostIdsBy(id);
        l = l.subList(Math.max(l.size() - 10, 0), l.size());
        Collections.reverse(l);
        return new Pair<String, List<Long>>(u.getBio(), l);
    }
}

package engine;

import java.util.List;
import java.time.LocalDate;
import java.util.TreeSet;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.Collections;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QuerySix.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491)
 */
public class QuerySix {
    /**
     * Método que responde à query 6.
     * @param TCDExample c Estrutura de dados principal.
     * @param int N Número de respostas a listar.
     * @param LocalDate begin Data de início.
     * @param LocalDate end Data de fim.
     * @return List Lista dos ids das respostas.
     */
    public static List<Long> resposta(TCDExample c, int N, LocalDate begin, LocalDate end) {
        List<Post> posts = c.getPostsBetween(begin, end);
        Comparator<Post> byScore =
            (Post p1, Post p2) -> {
                int scoreCmp = new Long(p1.getScore()).compareTo(p2.getScore());
                if (scoreCmp == 0) {
                    return new Long(p1.getId()).compareTo(p2.getId());
                }
                return scoreCmp;
            };
        TreeSet<Post> postsByScore = new TreeSet<Post>(byScore);
        posts.forEach(p -> postsByScore.add(p));
        List<Long> postList = postsByScore.stream().map(p -> p.getId()).collect(Collectors.toList());
        postList = postList.subList(Math.max(0, postList.size() - N), postList.size());
        Collections.reverse(postList);
        return postList;
    }
}

/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491
 */

package engine;

import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;
import java.util.Map.Entry;
import java.util.Iterator;
import java.util.TreeSet;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.Collections;
import common.Pair;
import li3.TADCommunity;

/**
 * Comparador de Posts por número de respostas (ordem crescente).
 */
class PostsByNumAnswersComparator implements Comparator<Post> {
    public int compare(Post p1, Post p2) {
        int numAnswerCmp = new Integer(p1.getNumAnswers()).compareTo(p2.getNumAnswers());
        if (numAnswerCmp == 0) {
            return new Long(p1.getId()).compareTo(p2.getId());
        }
        return numAnswerCmp;
    }
}

/**
 * Class QuerySeven.
 */
public class QuerySeven {
    /**
     * Método que responde à query 7.
     * @param TCDExample c Estrutura de dados principal.
     * @param int Número de perguuntas a incluir.
     * @param LocalDate Data inicial.
     * @param LocalDate Data final.
     * @return List Ids das N perguntas com mais respostas.
     */
    public static List<Long> resposta(TCDExample c, int N, LocalDate begin, LocalDate end) {
        List<Post> posts = c.getPostsBetween(begin, end);
        TreeSet<Post> postsByScore = new TreeSet<Post>(new PostsByNumAnswersComparator());
        posts.stream().filter(p -> p.getType() == PostType.QUESTION).forEach(p -> postsByScore.add(p));
        List<Long> postList = postsByScore.stream()
                .map(p -> p.getId()).collect(Collectors.toList());
        postList = postList.subList(Math.max(0, postList.size() - N), postList.size());
        Collections.reverse(postList);
        return postList;
    }
}

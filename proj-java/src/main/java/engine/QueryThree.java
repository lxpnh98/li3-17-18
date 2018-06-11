/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491
 */
package engine;

import java.util.List;
import java.time.LocalDate;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QueryThree.
 */
public class QueryThree {
    /**
     * Método que responde à query 3.
     * @param TCDExample c Estrutura de dados principal.
     * @param LocalDate Data inicial.
     * @param LocalDate Data final.
     * @return Pair (Número de perguntas, Número de respostas)
     */
    public static Pair<Long,Long> answersquestions(TCDExample c, LocalDate begin, LocalDate end) {
        long answers = 0, questions = 0;

        for(Post p: c.getPostsBetween(begin, end)){
            if (p.getType() == PostType.ANSWER) answers++;
            if (p.getType() == PostType.QUESTION) questions++;
        }

        Pair pair = new Pair(questions,answers);

        return pair;
    }
}o
/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491)
 */
package engine;

import common.Pair;
import li3.TADCommunity;
import java.util.Set;
import java.util.Iterator;

/**
 * Class QueryTen.
 */
public class QueryTen {
    /**
     * Método que responde à query 10.
     * @param TCDExample c Estrutura de dados principal.
     * @param long id Id da pergunta.
     * @return long Id da resposta.
     */
    public static long resposta(TCDExample c, long id) {
        double bestMedia = 0;
        long bestAnswer = -1;
        long answerTemp = -1;
        long scr, rep, vot,comt;
        double media;

        Post p = c.getPost(id);
        Iterator<Long> it = p.getAnswers().iterator();
        while(it.hasNext()) {
            answerTemp = it.next();
            Post answer = c.getPost(answerTemp);
            scr = answer.getScore();
            rep = c.getUserRep(answer.getUserId());
            vot = scr;
            comt = answer.getCommentCount();
            media = ((scr * 0.45) + (rep *0.25) + (vot * 0.2) + (comt * 0.1));

            if(media > bestMedia) {
                bestMedia = media;
                bestAnswer = answerTemp;
            }
        }
        return bestAnswer;
    }
}

/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491)
 */
package engine;

import java.util.ArrayList;
import java.util.List;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QueryTwo.
 */
public class QueryTwo {
	/**
     * Método que responde à query 2.
     * @param TCDExample c Estrutura de dados principal.
     * @param int N Número de utilizadores que se pretende listar.
     * @return List Lista dos N ids dos utilizadores.
     */
    public static List<Long> resposta(TCDExample c, int N) {
        List<Long> res = c.getUsersByPosts();
        return res.subList(0,N);
    }
}

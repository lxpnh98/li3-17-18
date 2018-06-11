package engine;

import java.util.ArrayList;
import java.util.List;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QueryEight.
 * @author Alexandre Mendonça Pinho (A82441)
 *          Joel Filipe Esteves Gama (A82202)
 *          Tiago Martins Pinheiro (A82491)
 */
public class QueryEight {
	/**
     * Método que responde à query 8.
     * @param TCDExample c Estrutura de dados principal.
     * @param int N Número de perguntas a listar.
     * @param String word Palara a procurar.
     * @return List Lista dos ids das perguntas.
     */
    public static List<Long> resposta(TCDExample c, int N, String word) {
        List<Long> res = c.getPostsByDate(word);
        return res.subList(0,N);
    }
}

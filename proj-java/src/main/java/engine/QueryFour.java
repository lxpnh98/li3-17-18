package engine;

import java.util.List;
import java.time.LocalDate;
import java.util.stream.Collectors;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QueryFour.
 * @author Alexandre Mendonça Pinho (A82441)
 *         Joel Filipe Esteves Gama (A82202)
 *         Tiago Martins Pinheiro (A82491)
 */
public class QueryFour {
	/**
     * Método que responde à query 4.
     * @param TCDExample c Estrutura de dados principal.
     * @param String tag Tag a procurar.
     * @param LocalDate begin Data de início.
     * @param LocalDate end Data de fim.
     * @return List Lista dos ids das perguntas.
     */
    public static List<Long> resposta(TCDExample c, String tag, LocalDate begin, LocalDate end){
        return c.getPostsBetween(begin, end).stream()
                   .filter(p -> p.getType() == PostType.QUESTION && p.hasTag(tag))
                       .map(Post::getId).collect(Collectors.toList());
    }
}

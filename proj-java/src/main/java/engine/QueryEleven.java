/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491
 */

package engine;

import java.util.List;
import java.time.LocalDate;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.Collections;
import common.Pair;
import li3.TADCommunity;

/**
 * Comparador de Tags por número de respostas (ordem crescente).
 */
class TagCountComparator implements Comparator<Long> {
    /** Map que contém o Id do user e o número de vezes que usou uma tag.*/
    private Map<Long,Integer> tagCounts;

    /** 
     * Atualiza o Map
     * @param Map m
     */
    public void setTagCounts(Map<Long,Integer> m) {
        this.tagCounts = m;
    }

    /**
     * Método que compara o número de tags usados por dois ids(Dois utilizadores).
     * @param t1 Id do primeiro user.
     * @param t2 Id do segundo user.
     * @return Resultado da comparação.
     */
    public int compare(Long t1, Long t2) {
        int countCmp = new Integer(this.tagCounts.get(t1)).compareTo(this.tagCounts.get(t2));
        if (countCmp == 0) {
            return new Long(t1).compareTo(t2);
        }
        return countCmp;
    }
}

/**
 * Class QueryEleven.
 */
public class QueryEleven {
    /**
     * Método que responde à query 11
     * @param TCDExample c Estrutura de dados principal.
     * @param Número de tags a incluir na resposta, a partir dos N utilizadores com melhor reputação.
     * @param LocalDate Data inicial.
     * @param LocalDate Data final.
     * @return List Ids das N tags mais utilizadas pelos N utilizadores com melhor reputação.
     */
    public static List<Long> resposta(TCDExample c, int N, LocalDate begin, LocalDate end) {
        List<Long> bestRep = c.getUsersByRep();
        final List<Long> NBestRep = bestRep.subList(Math.max(0, bestRep.size() - N), bestRep.size());
        List<Post> posts = c.getPostsBetween(begin, end).stream()
                                .filter(p -> NBestRep.contains(p.getUserId())).collect(Collectors.toList());
        HashMap<Long,Integer> tagCounts = new HashMap<>();
        TagCountComparator cmp = new TagCountComparator();
        cmp.setTagCounts(tagCounts);
        TreeSet<Long> mostUsedTags = new TreeSet<>(cmp);
        for (Post p : posts) {
            List<Long> tagIds = p.getTags().stream().map(s -> c.getTag(s).getId()).collect(Collectors.toList());
            for (Long id : tagIds) {
                if (tagCounts.containsKey(id)) {
                    tagCounts.put(id, tagCounts.get(id) + 1);
                } else {
                    tagCounts.put(id, 0);
                }
            }
        }
        tagCounts.keySet().forEach(id -> mostUsedTags.add(id));
        List<Long> tagList = mostUsedTags.stream().collect(Collectors.toList());
        tagList = tagList.subList(0, Math.min(tagList.size(), N));
        return tagList;
    }
}

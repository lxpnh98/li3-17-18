/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491)
 */
package engine;

import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;
import java.util.Iterator;
import java.util.Collections;
import java.util.stream.Collectors;
import java.util.LinkedHashSet;
import common.Pair;
import li3.TADCommunity;

/**
 * Class QueryNine.
 */
public class QueryNine {
	/**
     * Método que responde à query 9.
     * @param TCDExample c Estrutura de dados principal.
     * @param int N Número de posts que se pretende listar.
     * @param long Id1 do primeiro utilizador.
     * @param long Id2 do segundo utilizador.
     * @return List Lista dos N ids dos posts.
     */
	public static List<Long> resposta(TCDExample c, int N, long id1, long id2){
		long id;
		List<Long> perguntas = new ArrayList();
		List<Long> postsid1 = c.getPostIdsBy(id1);
		List<Long> postsid2 = c.getPostIdsBy(id2);
		List<Long> posts1 = new ArrayList();
		List<Long> posts2 = new ArrayList();

		for (long l: postsid1) {
			if ((c.getPost(l)) != null){
				if (c.getPost(l).getType() == PostType.QUESTION){
        			posts1.add(l);
				}
				else if (c.getPost(l).getType() == PostType.ANSWER){
					id = c.getPost(l).getParentId();
        			posts1.add(id);
				}
			}
      	}

      	for (long l: postsid2) {
			if ((c.getPost(l)) != null){
				if (c.getPost(l).getType() == PostType.QUESTION){
        			posts2.add(l);
				}
				else if (c.getPost(l).getType() == PostType.ANSWER){
					id = c.getPost(l).getParentId();
        			posts2.add(id);
				}
			}
    	}
    	posts1.retainAll(posts2);
      	return posts1.stream().distinct().collect(Collectors.toList());
	}
}
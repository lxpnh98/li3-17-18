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
 * Class QueryOne.
 */
public class QueryOne {
    /**
     * Método que responde à query 1.
     * @param TCDExample c Estrutura de dados principal.
     * @param long Id do Post
     * @return Pair (Título do post, Nome de utilizador do autor do post)
     */
    public static Pair<String,String> resposta(TCDExample c, long id){
        String titulo = "";
        String nome = "";
        Post p = c.getPost(id);
        if (p != null) {
            titulo = p.getTitle();
            nome = c.getUser(p.getUserId()).getDisplayName();
        }
        return new Pair<String,String>(titulo, nome);
    }
}
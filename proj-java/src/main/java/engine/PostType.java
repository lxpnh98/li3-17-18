/*
 * @author Alexandre Mendonça Pinho (A82441)
           Joel Filipe Esteves Gama (A82202)
           Tiago Martins Pinheiro (A82491)
 */

package engine;

/**
 * Enum para o Tipo do Post.
 */
public enum PostType {
    QUESTION(1),
    ANSWER(2),
    OTHERS(3);

    /** Valor do PostType (1- Question, 2 - Answer, 3- Others) */
    private int value;

    /**
     * Atualiza o valor do PostType.
     * @param int value.
     */
    private PostType (int value) {
        this.value = value;
    }

    /**
     * Devolve o valor do enum.
     * @return int Valor do enum.
     */ 
    public int getValue() {
        return value;
    }
}

package engine;

import java.util.List;
import java.time.LocalDate;
import java.util.stream.Collectors;
import common.Pair;
import li3.TADCommunity;

public class QueryFour {
    public static List<Long> resposta(TCDExample c, String tag, LocalDate begin, LocalDate end){
        System.out.println("Number of posts between: " + c.getPostsBetween(begin, end).size());
        return c.getPostsBetween(begin, end).stream()
                   .filter(p -> p.getType() == PostType.QUESTION && p.hasTag(c.getTag(tag).getId()))
                       .map(Post::getId).collect(Collectors.toList());
    }
}

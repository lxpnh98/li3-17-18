package engine;

import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;
import java.util.Map.Entry;
import java.util.Iterator;
import java.util.TreeSet;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.Collections;
import common.Pair;
import li3.TADCommunity;

public class QuerySix {
    public static List<Long> resposta(TCDExample c, int N, LocalDate begin, LocalDate end) {
        List<Post> posts = c.getPostsBetween(begin, end);
        Comparator<Post> byScore =
            (Post p1, Post p2) -> new Long(p1.getScore()).compareTo(p2.getScore());
        TreeSet<Post> postsByScore = new TreeSet<Post>(byScore);
        posts.forEach(p -> postsByScore.add(p));
        List<Long> postList = postsByScore.stream().map(p -> p.getId()).collect(Collectors.toList());
        postList = postList.subList(Math.max(0, postList.size() - N), postList.size());
        Collections.reverse(postList);
        return postList;
    }
}

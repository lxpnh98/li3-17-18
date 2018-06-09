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
<<<<<<< HEAD

	public static List<Long> answersmostvoted(TCDExample c, int N, LocalDate begin, LocalDate end) {
		Long key;
		List<Long> ids = new ArrayList();
		TreeMap<Long,List<Post>> postsPorScore = new TreeMap<>();

		for(Post p: c.getPostsBetween(begin, end)){
			if (p.getType() == PostType.ANSWER){
				key = p.getScore();
				if (postsPorScore.get(key) == null){
					ArrayList<Post> posts = new ArrayList<>();
            		posts.add(p.clone());
            		postsPorScore.put(key, posts);
        		} else {
	            	postsPorScore.get(key).add(p.clone());
    	    	}
    	    }
    	}

    	ids = idsPorScore(postsPorScore,N);

		return ids;
	}

	public static List<Long> idsPorScore(TreeMap posts, int N){
        List<Long> postsPorScore = new ArrayList();

        Iterator ittwo = posts.keySet().iterator();
        while (ittwo.hasNext()) {
            	for (Post p : ((List<Post>)posts.get(ittwo.next()))) {
                	if (postsPorScore.size() < N) {postsPorScore.add(p.getId());}
            	}
        }

        return postsPorScore;
=======
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
>>>>>>> 001750da587cda60ef01157c349042e8f3c8d828
    }
}

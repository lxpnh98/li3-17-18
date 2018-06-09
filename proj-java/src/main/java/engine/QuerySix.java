package engine;

import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;
import java.util.Map.Entry;
import java.util.Iterator;
import java.util.TreeMap;
import common.Pair;
import li3.TADCommunity;

public class QuerySix {

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
    }
}

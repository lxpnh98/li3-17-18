package engine;

import java.util.List;
import java.time.LocalDate;
import common.Pair;
import li3.TADCommunity;

public class QueryThree {

	public static Pair<Long,Long> answersquestions(TCDExample c, LocalDate begin, LocalDate end) {
		long answers = 0, questions = 0;

		for(Post p: c.getPostsBetween(begin, end)){
			if (p.getType() == PostType.ANSWER) answers++;
			if (p.getType() == PostType.QUESTION) questions++;
		}

		Pair pair = new Pair(questions,answers);

		return pair;
	}
}
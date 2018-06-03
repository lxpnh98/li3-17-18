package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;
import common.Pair;
import li3.TADCommunity;

public class QueryOne {
	
	public static Pair<String,String> resposta(long id, List<Post> postList, List<User> userList, Pair<String,String> res){
		String titulo = "";
		String nome = "";

		for (Post p : postList) {
			if (p.getId() == id) {
				titulo = p.getTitle();
				System.out.println(titulo);
				for (User u : userList) {
					if (u.getId() == p.getUserId()) {
						nome = u.getDisplayName();
					}
				}
			}
		}

		res.setFst(titulo);
		res.setSecond(nome);
		return res;
	}
}

package engine;

import java.util.ArrayList;
import java.util.List;
import java.lang.String;
import java.lang.Long;
import common.Pair;
import li3.TADCommunity;

public class QueryOne {
	private String titulo;
	private String nome;
	private Pair<String,String> pair;

	public Pair<String,String> infoFromPost(long id){

		for(Post p: post){
			if (p.getId() == id){
				this.titulo = p.getTitle();
				for (User u: usersHandler.getUserList()){
					if (u.getId() == p.getUserId()){
						this.nome = u.getDisplayName();
					}
				}
			}
		}
		this.pair = new Pair<>(titulo, nome);

		return this.pair;
	}
}

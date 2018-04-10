/**
@file community.h
Definição de funções acesso à estrutura de dados principal.
*/

#ifndef __COMMUNITY__
#define __COMMUNITY__

#include "user.h"
#include "tag.h"
#include "post.h"
#include "linked_list.h"

typedef struct TCD_community *TAD_community;

TAD_community init_community();

void add_user(TAD_community com, USER user);

void add_tag(TAD_community com, TAG tag);

void add_post(TAD_community com, POST post, LINKED_LIST *answers_to_add);

USER get_user(TAD_community com, long id);

POST get_post(TAD_community com, long id);

TAG get_tag_from_id(TAD_community com, long id);

TAG get_tag_from_name(TAD_community com, char *name);

char *get_author_name(TAD_community com, POST p);

char *get_question_title(TAD_community com, POST p);

TAD_community clean_community(TAD_community com);

#endif

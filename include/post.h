/**
@file post.h
Definição de funções acesso à estrutura de dados POST.
*/

#ifndef __POST__
#define __POST__

#include "date.h"
#include "list.h"

typedef struct post *POST;

enum post_type {
    QUESTION = 1,
    ANSWER = 2
};

POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId,
                 char *userDisplayName, char *title, long parentId, int answer_count,
                 long score, char *CreationDate, LONG_list tags, long get_comment_count);

long get_post_id(POST p);

int get_type(POST p);

long get_user_id(POST p);

char *get_user_display_name(POST p);

char *get_title(POST p);

long get_parent_id(POST p);

long get_score(POST p);

int get_answer_count(POST p);

void add_answer(POST p, long id);

LONG_list get_answers(POST p);

int has_tag(POST p, long tag_id);

int get_type(POST p);

Date get_CreationDate(POST p);

int get_ntags(POST p);

LONG_list get_tags(POST p);

long get_comment_count(POST p);

#endif

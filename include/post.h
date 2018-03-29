#ifndef __POST__
#define __POST__

#include "date.h"

typedef struct post *POST;

enum post_type {
    QUESTION = 1,
    ANSWER = 2
};

POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId,
                 char *userDisplayName, char *title, long parentId, int answer_count, long score, char *CreationDate, int ntags, char *tags[]);

long get_post_id(POST p);

int get_type(POST p);

long get_user_id(POST p);

char *get_user_display_name(POST p);

char *get_title(POST p);

long get_parent_id(POST p);

long get_score(POST p);

int get_answer_count(POST p);

int has_tag(POST p, char *tag);

int get_type(POST p);

Date get_CreationDate(POST p);

#endif

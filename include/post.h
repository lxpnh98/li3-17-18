#ifndef __POST__
#define __POST__

#include "date.h"

typedef struct post* POST;

enum post_type {
    QUESTION = 1,
    ANSWER = 2
};

POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId,
                 char *userDisplayName, char *title, long parentId, char *CreationDate);

char *get_title(POST p);

long get_post_id(POST p);

long get_user_id(POST p);

char *get_user_display_name(POST p);

long get_parent_id(POST p);

Date get_CreationDate(POST p);

int get_type(POST p);

#endif

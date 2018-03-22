#ifndef __POST__
#define __POST__
typedef struct post* POST;

enum post_type {
    QUESTION = 1,
    ANSWER = 2
};

POST create_post(long id, enum post_type type, long AcceptedAnswer);

char *get_title();

char *get_author_name();

#endif

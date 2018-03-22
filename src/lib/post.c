#include <string.h>
#include <stdlib.h>
#include "post.h"
#include "common.h"

struct post {
    long id;                /** Id do post */
    enum post_type type;    /** Id pergunta = 1; Id resposta = 2*/
    long AcceptedAnswer;    /** Id da resposta aceite; -1 em caso de ser uma pergunta*/
};

POST create_post(long id, enum post_type type, long AcceptedAnswer) {
  POST p = malloc(sizeof(struct post));
  p->id = id;
  p->type = type;
  p->AcceptedAnswer = AcceptedAnswer;
  return p;
}

char *get_title() {
    return "test_title";
}

char *get_author_name() {
    return "test_author";
}


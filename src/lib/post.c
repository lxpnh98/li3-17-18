#include <string.h>
#include <stdlib.h>
#include "post.h"
#include "common.h"
#include "community.h"

struct post {
    long id;                /** Id do post */
    enum post_type type;    /** Id pergunta = 1; Id resposta = 2 */
    long AcceptedAnswer;    /** Id da resposta aceite; -1 em caso de ser uma pergunta */
    long userId;            /** Id do User criador da pergunta/resposta */ 
    char *userDisplayName;  /** Nomde do utilizador, caso não tenha user Id */
};

POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId, char *userDisplayName) {
    POST p = malloc(sizeof(struct post));
    p->id = id;
    p->type = type;
    p->AcceptedAnswer = AcceptedAnswer;
    p->userId = userId;
    p->userDisplayName = userDisplayName;
    return p;
}

char *get_title(POST p) {
    return "test_title";
}

long get_user_id(POST p) {
    return p->userId;
}

char *get_user_display_name(POST p){
    return p->userDisplayName;
}
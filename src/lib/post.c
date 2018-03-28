#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "post.h"
#include "date.h"
#include "common.h"
#include "community.h"

struct post {
    long id;                /** Id do post */
    enum post_type type;    /** Id pergunta = 1; Id resposta = 2 */
    long AcceptedAnswer;    /** Id da resposta aceite; -1 em caso de ser uma pergunta */
    long userId;            /** Id do User criador da pergunta/resposta */
    char *userDisplayName;  /** Nomde do utilizador, caso não tenha user Id */
    char *title;            /** Titulo da pergunta, em caso de ser resposta é NULL */
    long parentId;          /** No caso de ser resposta, id do pai, caso contrário -1 */
    char *CreationDate;     /** String da data criação do post */
};

POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId,
                 char *userDisplayName, char *title, long parentId, char *CreationDate) {
    POST p = malloc(sizeof(struct post));
    p->id = id;
    p->type = type;
    p->AcceptedAnswer = AcceptedAnswer;
    p->userId = userId;
    p->userDisplayName = userDisplayName;
    p->title = title;
    p->parentId = parentId;
    p->CreationDate = CreationDate;
    return p;
}

char *get_title(POST p) {
    return p->title;
}

long get_post_id(POST p) {
    return p->id;
}

long get_user_id(POST p) {
    return p->userId;
}

char *get_user_display_name(POST p){
    return p->userDisplayName;
}

long get_parent_id(POST p) {
    return p->parentId;
}

Date get_CreationDate(POST p){
    int dia, mes, ano;
    char *CreationDate = p->CreationDate;
    sscanf(CreationDate, "%d-%d-%d",&ano ,&mes,&dia);
    Date d = createDate(dia, mes, ano);
    return d;
}

int get_type(POST p) {
    return p->type;
}
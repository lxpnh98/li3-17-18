#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "post.h"
#include "date.h"
#include "list.h"
#include "common.h"
#include "community.h"

struct post {
    long id;               /** Id do post */
    enum post_type type;   /** Id pergunta = 1; Id resposta = 2 */
    long AcceptedAnswer;   /** Id da resposta aceite; -1 em caso de ser uma pergunta */
    long userId;           /** Id do User criador da pergunta/resposta */
    char *userDisplayName; /** Nomde do utilizador, caso não tenha user Id */
    char *title;           /** Titulo da pergunta, em caso de ser resposta é NULL */
    long parentId;         /** No caso de ser resposta, id do pai, caso contrário -1 */
    int answer_count;      /** Número de responstas, caso seja pergunta */
    LONG_list answers;     /** Lista dos ids das respostas, caso seja pergunta */
    long score;            /** Score dos posts */
    char *CreationDate;    /** String da data criação do post */
    int ntags;             /** Número de tags do post */
    char **tags;           /** Vetor de tags do post */
};

POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId,
                 char *userDisplayName, char *title, long parentId, int answer_count, long score, char *CreationDate, int ntags,
                 char *tags[]) {
    int i;
    POST p = malloc(sizeof(struct post));
    p->id = id;
    p->type = type;
    p->AcceptedAnswer = AcceptedAnswer;
    p->userId = userId;
    p->userDisplayName = userDisplayName;
    p->title = title;
    p->parentId = parentId;
    p->answer_count = answer_count;
    p->answers = create_list(answer_count);
    for (i = 0; i < answer_count; i++)
        set_list(p->answers, i, -1);    // para não conter um id válido ao acaso
    p->score = score;
    p->CreationDate = CreationDate;
    p->ntags = ntags;
    p->tags = malloc(sizeof(char *) * ntags);
    for (i = 0; i < ntags; i++) {
        p->tags[i] = mystrdup(tags[i]);
    }
    return p;
}

long get_post_id(POST p) {
    return p->id;
}

int get_type(POST p) {
    return p->type;
}

long get_user_id(POST p) {
    return p->userId;
}

char *get_user_display_name(POST p) {
    return p->userDisplayName;
}

char *get_title(POST p) {
    return p->title;
}

long get_parent_id(POST p) {
    return p->parentId;
}

long get_score(POST p) {
    return p->score;
}

int get_answer_count(POST p) {
    return p->answer_count;
}

void add_answer(POST p, long id) {
    push_insert(p->answers, 0, id);
}

LONG_list get_answers(POST p) {
    return p->answers;
}

Date get_CreationDate(POST p) {
    int dia, mes, ano;
    char *CreationDate = p->CreationDate;
    sscanf(CreationDate, "%d-%d-%d", &ano, &mes, &dia);
    Date d = createDate(dia, mes, ano);
    return d;
}

int has_tag(POST p, char *tag) {
    int i;
    for (i = 0; i < p->ntags; i++) {
        if (strcmp(p->tags[i], tag) == 0)
            return 1;
    }
    return 0;
}

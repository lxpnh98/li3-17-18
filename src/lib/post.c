/**
@file post.c
Definição de funções acesso à estrutura de dados POST.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "post.h"
#include "date.h"
#include "list.h"
#include "common.h"
#include "community.h"

/** \brief Estrutura que armazena a informação do post */
struct post {
    /** \brief Id do post */
    long id;
    /** \brief Id pergunta = 1; Id resposta = 2 */
    enum post_type type;
    /** \brief Id da resposta aceite; -1 em caso de ser uma pergunta */
    long AcceptedAnswer;
    /** \brief Id do User criador da pergunta/resposta */
    long userId;
    /** \brief Nomde do utilizador, caso não tenha user Id */
    char *userDisplayName;
    /** \brief Titulo da pergunta, em caso de ser resposta é NULL */
    char *title;
    /** \brief No caso de ser resposta, id do pai, caso contrário -1 */
    long parentId;
    /** \brief Número de responstas, caso seja pergunta */
    int answer_count;
    /** \brief Lista dos ids das respostas, caso seja pergunta */
    LONG_list answers; // TODO: tornar a lista de respostas numa lista ligada (e incluir tamanho na lista ligada)
    /** \brief Score dos posts */
    long score;
    /** \brief String da data criação do post */
    char *CreationDate;
    /** \brief Vetor de tags do post */
    LONG_list tags;
    /** \brief Número de comentários */
    long comment_count;
};

/**
\brief Função que cria um post.
@param id Id do post.
@param post_type type Id da resposta aceite.
@param AcceptedAnswer Id do utilizador criador do post.
@param userId Id do utilizador criador do post.
@param userDisplayName Nome do utilizador.
@param title Título do post.
@param parentId Id do pai do post.
@param answer_count Número de respostas.
@param score Pontuação do post.
@param CreationDate String da data de criação do post.
@param tags Vetor de tags do post.
@param comment_count Número de comentários.
@returns POST Post.
*/
POST create_post(long id, enum post_type type, long AcceptedAnswer, long userId,
                 char *userDisplayName, char *title, long parentId, int answer_count,
                 long score, char *CreationDate, LONG_list tags, long comment_count) {
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
    if (tags != NULL) {
        p->tags = clone_list(tags);
    } else {
        p->tags = NULL;
    }
    p->comment_count = comment_count;
    return p;
}

/**
\brief Função que devolve o id de um post.
@param p Estrutura do tipo post.
@returns long Id do post.
*/
long get_post_id(POST p) {
    return p->id;
}

/**
\brief Função que devolve o id do tipo de um post.
@param p Estrutura do tipo post.
@returns int Tipo de post.
*/
int get_type(POST p) {
    return p->type;
}

/**
\brief Função que devolve o id do utilizador criador de um post.
@param p Estrutura do tipo post.
@returns long Id do utilizador.
*/
long get_user_id(POST p) {
    return p->userId;
}

/**
\brief Função que devolve o nome do utilizador criador do post.
@param p Estrutura do tipo post.
@returns char Nome do utilizador.
*/
char *get_user_display_name(POST p) {
    return p->userDisplayName;
}

/**
\brief Função que devolve o título do post.
@param p Estrutura do tipo post.
@returns char Título do post.
*/
char *get_title(POST p) {
    return p->title;
}

/**
\brief Função que devolve o id do pai do post.
@param p Estrutura do tipo post.
@returns long Id do pai do post
*/
long get_parent_id(POST p) {
    return p->parentId;
}

/**
\brief Função que devolve a pontuação do post.
@param p Estrutura do tipo post.
@returns long Pontuação do post.
*/
long get_score(POST p) {
    return p->score;
}

/**
\brief Função que devolve o número de respostas de um post.
@param p Estrutura do tipo post.
@returns int Número de respostas.
*/
int get_answer_count(POST p) {
    return p->answer_count;
}

/**
\brief Função que adiciona uma resposra a um post.
@param p Estrutura do tipo post.
@param id Id da resposta.
*/
void add_answer(POST p, long id) {
    push_insert(p->answers, 0, id);
}

/**
\brief Função que devolve a lista das respostas a um post.
@param p Estrutura do tipo post.
@returns LONG_list Lista das respostas.
*/
LONG_list get_answers(POST p) {
    return p->answers;
}

/**
\brief Função que devolve a data de criação do post.
@param p Estrutura do tipo post.
@returns Date Data de criação de um post.
*/
Date get_CreationDate(POST p) {
    int dia, mes, ano;
    char *CreationDate = p->CreationDate;
    sscanf(CreationDate, "%d-%d-%d", &ano, &mes, &dia);
    Date d = createDate(dia, mes, ano);
    return d;
}

/**
\brief Função que verifica se um post tem uma dada tag.
@param p Estrutura do tipo post.
@param tag_id Id da tag.
@returns int Inteiro com valor boleano.
*/
int has_tag(POST p, long tag_id) {
    int i;
    int size = get_ntags(p);
    for (i = 0; i < size; i++) {
        if (get_list(p->tags, i) == tag_id)
            return 1;
    }
    return 0;
}

/**
\brief Função que devolve o número de tags de um post.
@param p Estrutura do tipo post.
@returns int Número de tags.
*/
int get_ntags(POST p) {
    if (p->tags) {
        return get_list_size(p->tags);
    } else
        return 0;
}

/**
\brief Função que devolve a lista das tags de um post.
@param p Estrutura do tipo post.
@returns LONG_list Lista das tags.
*/
LONG_list get_tags(POST p) {
    if (p->tags) {
        return clone_list(p->tags);
    } else
        return NULL;
}

/**
\brief Função que devolve o número de comentários de um post.
@param p Estrutura do tipo post.
@returns long Número de comentários.
*/
long get_comment_count(POST p) {
    return p->comment_count;
}

// TODO: implementar free_post()

/**
@file tag.c
Funções que operam sobre as Tags.
*/

#include <string.h>
#include <stdlib.h>
#include "tag.h"
#include "common.h"

/** \brief Estrutura que armazena a informação da tag */
struct tag {
	/** \brief Id da tag */
    long id;
    /** \brief String do Nome da tag */
    char *name;
};

/**
\brief Função que cria uma tag.
@param id Id da tag.
@param tagName String do nome da tag.
@returns TAG Tag.
*/
TAG create_tag(long id, char *tagName) {
    TAG t = malloc(sizeof(struct tag));
    t->id = id;
    t->name = mystrdup(tagName);
    return t;
}

/**
\brief Função que devolve o id de uma dada tag.
@param t Estrutura do tipo tag.
@returns long Id da tag.
*/
long get_tag_id(TAG t) {
    return t->id;
}

/**
\brief Função que devolve a string do nome de uma dada tag.
@param t Estrutura do tipo tag.
@returns char String do nome da tag.
*/
char *get_tagName(TAG t) {
    if (t)
        return t->name;
    return NULL;
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param t Estrutura do tipo tag.
*/
void free_tag(TAG t) {
    if (t)
        free(t);
}

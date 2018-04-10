/**
@file linked_list.c
Definição de funções acesso à estrutura de dados LINKED_LIST.
*/

#include <stdlib.h>             // malloc, free
#include <assert.h>             // assert
#include "linked_list.h"

/** \brief Estrutura que representa uma lista ligada */
struct linked_list {
    /** \brief Informação do elemento da lista */
    void *data;
    /** \brief Apontador para o próximo elemento da lista */
    LINKED_LIST next;
};

/**
\brief Função que inicia uma lista ligada.
@returns LINKED_LIST Lista ligada.
*/
LINKED_LIST init_linked_list() {
    LINKED_LIST new = malloc(sizeof(struct linked_list));
    new->data = NULL;
    new->next = NULL;
    return new;
}


/**
\brief Função que adiciona informação a uma dada lista.
@param l Estrutura do tipo lista ligada.
@param data Informação a adicionar.
@returns LINKED_LIST Lista ligada.
*/
LINKED_LIST add(LINKED_LIST l, void *data) {
    LINKED_LIST e = init_linked_list();
    if (e == NULL)
        return NULL;
    e->data = data;
    e->next = l;
    return e;
}

/**
\brief Função que remove a cabeça de uma dada lista ligada.
@param l Estrutura do tipo lista ligada.
@returns LINKED_LIST Lista ligada.
*/
LINKED_LIST remove_head(LINKED_LIST l) {
    assert(next(l));
    LINKED_LIST new = next(l);
    free(l);
    return new;
}

/**
\brief Função que altera o apontador para o próximo elemento da lista.
@param l Estrutura do tipo lista ligada.
@returns LINKED_LIST Lista ligada.
*/
LINKED_LIST next(LINKED_LIST l) {
    assert(l != NULL);
    return l->next;
}

/**
\brief Função que retorna a informação de um elemento da lista.
@param l Estrutura do tipo lista ligada.
*/
void *get_data(LINKED_LIST l) {
    assert(l != NULL);
    return l->data;
}


/**
\brief Função que liberta a memória utilizada pela estrutura de dados.
@param l Estrutura do tipo lista ligada.
*/
void free_linked_list(LINKED_LIST l) {
    assert(l != NULL);
    LINKED_LIST n = next(l);
    if (n)
        free_linked_list(n);
    free(l);
}

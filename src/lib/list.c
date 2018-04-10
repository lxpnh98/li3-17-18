/**
@file list.c
Funções que operam sobre listas.
*/

#include <stdlib.h>
#include "list.h"

/** \brief Estrutura que representa uma lista de longs */
struct llist {
    /** \brief Tamanho da lista */
    int size;
    /** \brief Apontador para a uma estrutura LONG_list */
    long *list;
};

/**
\brief Função que cria uma lista.
@param size Tamanho da lista.
@returns LONG_list Lista.
*/
LONG_list create_list(int size) {
    if (size <= 0)
        return NULL;
    LONG_list l = malloc(sizeof(struct llist));
    l->size = size;
    l->list = malloc(sizeof(long) * size);
    return l;
}

/**
\brief Função que devolve um elemento da lista num dado índice.
@param l Estrutura do tipo lista.
@param index Índice a procurar.
@returns long Id do conteudo da lista.
*/
long get_list(LONG_list l, int index) {
    return l->list[index];
}

/**
\brief Função que atualiza um valor de uma lista num dado índice.
@param l Estrutura do tipo lista.
@param index Índice a procurar.
@param value Novo valor a inserir na lista.
*/
void set_list(LONG_list l, int index, long value) {
    l->list[index] = value;
}

/**
\brief Função que devolve o tamanho de uma lista.
@param l Estrutura do tipo lista.
@returns int Tamanho da lista.
*/
int get_list_size(LONG_list l) {
    return l->size;
}

/**
\brief Função que retira um elemento da lista num dado índice.
@param l Estrutura do tipo lista.
@param index Índice a procurar.
@param value Valor a retirar.
*/
void push_insert(LONG_list l, int index, long value) {
    int i;
    for (i = l->size - 1; i > index; i--) { // TODO: usar memcpy() para copiar elementos
        l->list[i] = l->list[i - 1];
    }
    l->list[i] = value;
}

/**
\brief Função que clona uma lista.
@param l Estrutura do tipo lista.
@returns LONG_list Lista.
*/
LONG_list clone_list(LONG_list l) {
    LONG_list r = create_list(l->size);
    int i;
    for (i = 0; i < l->size; i++) {
        set_list(r, i, get_list(l, i));
    }
    return r;
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param l Estrutura do tipo lista.
*/
void free_list(LONG_list l) {
    if (l) {
        free(l->list);
        free(l);
    }
}

/**
@file linked_list.h
Definição de funções acesso à estrutura de dados LINKED_LIST.
*/

#ifndef __LINKED_LIST__
#define __LINKED_LIST__

typedef struct linked_list *LINKED_LIST;

/** Inicializa lista ligada com uma sentinela. Retorna NULL se falhar. */
LINKED_LIST init_linked_list();

/** Adiciona um nodo na cabeça da lista. Retorna a nova lista se suceder, e
 * NULL se falhar. */
LINKED_LIST add(LINKED_LIST l, void *data);

/** Retira nodo da cabeça da lista, dada uma lista não vazia. Retorna a nova
 * lista. */
LINKED_LIST remove_head(LINKED_LIST l);

/** Retorna apontador para o próximo nodo, dada uma lista válida (!= NULL).
 * Retorna NULL se a lista for vazia.*/
LINKED_LIST next(LINKED_LIST l);

/** Retorna o apontador para os dados do nodo atual (NULL se lista for vazia),
 * dada uma lista válida. */
void *get_data(LINKED_LIST l);

/** Liberta a memória alocada por todos os elementos duma lista válida. */
void free_linked_list(LINKED_LIST l, void (*f)(void *));

#endif

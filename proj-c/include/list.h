/**
@file list.h
Definição de funções acesso à estrutura de dados LONG_list.
*/

#ifndef __LONG_LIST__
#define __LONG_LIST__

typedef struct llist *LONG_list;

LONG_list create_list(int size);

long get_list(LONG_list l, int index);

void set_list(LONG_list l, int index, long value);

int get_list_size(LONG_list l);

/** Insere um elemento numa posição, empurrando os seguintes uma vez para a
 * frente, e descarta o último elemento. */
void push_insert(LONG_list l, int index, long value);

LONG_list clone_list(LONG_list l);

void free_list(LONG_list l);

#endif

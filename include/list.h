#ifndef __LONG_LIST__
#define __LONG_LIST__

typedef struct llist * LONG_list;

LONG_list create_list(int size);

long get_list(LONG_list l, int index);

void set_list(LONG_list l, int index, long value);

/** Insere um elemento numa posição, empurrando os seguintes uma vez para a
 * frente, e descarta o último elemento. */
void push_insert(LONG_list l, int index, long value);

void free_list(LONG_list l);

#endif

#include <stdlib.h>
#include "list.h"

struct llist { 
    int size;
    long * list;
};

LONG_list create_list(int size) {
    if(size <= 0) return NULL;
    LONG_list l = malloc(sizeof(struct llist));
    l->size = size;
    l->list = malloc(sizeof(long) * size);
    return l;
}

long get_list(LONG_list l, int index) {
    return l->list[index]; 
}

void set_list(LONG_list l, int index, long value) {
    l->list[index] = value;
}

void push_insert(LONG_list l, int index, long value) {
    int i;
    for (i = l->size - 1; i > index; i--) {
        l->list[i] = l->list[i - 1];
    }
    l->list[i] = value;
}

void free_list(LONG_list l) {
    if(l) {
        free(l->list);
        free(l);
    }
}


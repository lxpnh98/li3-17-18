#include <stdlib.h>
#include "list.h"

struct llist {
    int size;
    long *list;
};

LONG_list create_list(int size) {
    if (size <= 0)
        return NULL;
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

int get_list_size(LONG_list l) {
    return l->size;
}

void push_insert(LONG_list l, int index, long value) {
    int i;
    for (i = l->size - 1; i > index; i--) {
        l->list[i] = l->list[i - 1];
    }
    l->list[i] = value;
}

LONG_list clone_list(LONG_list l) {
    LONG_list r = create_list(l->size);
    int i;
    for (i = 0; i < l->size; i++) {
        set_list(r, i, get_list(l, i));
    }
    return r;
}

void free_list(LONG_list l) {
    if (l) {
        free(l->list);
        free(l);
    }
}

#include <stdlib.h> // malloc, free
#include <assert.h> // assert
#include "linked_list.h"

struct linked_list {
    void *data;
    LINKED_LIST next;
};

LINKED_LIST init_linked_list() {
    LINKED_LIST new = malloc(sizeof(struct linked_list));
    new->data = NULL;
    new->next = NULL;
    return new;
}

LINKED_LIST add(LINKED_LIST l, void *data) {
    LINKED_LIST e = init_linked_list();
    if (e == NULL) return NULL;
    e->data = data;
    e->next = l;
    return e;
}

LINKED_LIST remove_head(LINKED_LIST l) {
    assert(next(l));
    LINKED_LIST new = next(l);
    free(l);
    return new;
}

LINKED_LIST next(LINKED_LIST l) {
    assert(l != NULL);
    return l->next;
}

void *get_data(LINKED_LIST l) {
    assert(l != NULL);
    return l->data;
}

void free_linked_list(LINKED_LIST l) {
    assert(l != NULL);
    LINKED_LIST n = next(l);
    if (n) free_linked_list(n);
    free(l);
}


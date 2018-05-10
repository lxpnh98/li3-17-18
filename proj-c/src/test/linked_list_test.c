#include <stdio.h>              // printf
#include <stdlib.h>             // random
#include <time.h>               // time
#include "linked_list.h"

enum {
    DATA_SIZE = 10,
    DATA_MAX_VALUE = 100,
};

int main() {
    int i;
    int *d;
    int test_data[DATA_SIZE];

    // introduzir dados aleatórios
    srand(time(NULL));
    for (i = 0; i < DATA_SIZE; i++) {
        test_data[i] = rand() % DATA_MAX_VALUE;
    }

    // inicializar a lista como uma lista vazia
    LINKED_LIST l = init_linked_list();
    for (i = 0; i < DATA_SIZE; i++) {
        l = add(l, &test_data[i]);
    }

    // iterar pela lista e imprimir valores
    LINKED_LIST x = l;
    while (next(x)) {
        d = get_data(x);
        printf("%d\n", *d);
        x = next(x);
    }

    // remover um a um os elementos da lista
    x = l;
    while (next(x)) {
        printf("Removed element at %p\n", x);
        x = remove_head(x);
    }

    // libertar toda a memória ocupada pela lista (redundante neste caso devido
    // ao anterior ciclo
    free_linked_list(l, NULL);
}

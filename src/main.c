/**
@file main.c
Função main() do programa.
*/

#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <stdlib.h>
#include "pair.h"
#include "list.h"
#include "date.h"
#include "community.h"

/**
\brief Função main do programa.
@returns Sucesso da função main.
*/
int main(int argc, char *argv[]) {
    int i;
    if (argc < 2) {
        perror("Missing argument");
        return -1;
    }
    TAD_community c = init();

    load(c, argv[1]);

    // query 1
    printf("Query 1:\n");
    for (i = 1; i < 20; i++) {
        STR_pair pair = info_from_post(c, i);
        if (pair)
            printf("%s %s\n", get_fst_str(pair), get_snd_str(pair));
    }

    // Query 2
    printf("Query 2:\n");
    LONG_list most_active = top_most_active(c, 15);
    for (i = 0; i < 15; i++) {
        USER u = get_user(c, get_list(most_active, i));
        printf("%s - %d\n", get_display_name(u), get_post_count(u));
    }

    // Query 3
    printf("Query 3:\n");
    Date d1 = createDate(1, 1, 2000);
    Date d2 = createDate(1, 1, 2028);

    LONG_pair l;
    l = (total_posts(c, d1, d2));
    printf("%li %li\n", get_fst_long(l), get_snd_long(l));

    // Query 4
    printf("Query 4:\n");
    LONG_list ll = questions_with_tag(c, "root-access", d1, d2);
    if (ll != NULL) {           // mais que 0 elementos
        for (i = 0; i < get_list_size(ll); i++) {
            POST p = get_post(c, get_list(ll, i));
            printf("%ld - %s\n", get_post_id(p), get_title(p));
        }
    }
    // Query 5
    printf("Query 5:\n");
    USER u2;
    u2 = get_user_info(c, 10); 
   printf("%ld - %s\n", get_id(u2), get_bio(u2));

    // Query 6
    printf("Query 6:\n");
    ll = most_voted_answers(c, 15, d1, d2);
    if (ll != NULL) {           // mais que 0 elementos
        for (i = 0; i < get_list_size(ll); i++) {
            POST p = get_post(c, get_list(ll, i));
            printf("%ld - %ld\n", get_post_id(p), get_score(p));
        }
    }
    // Query 7
    printf("Query 7:\n");
    ll = most_answered_questions(c, 15, d1, d2);
    if (ll != NULL) {           // mais que 0 elementos
        for (i = 0; i < get_list_size(ll); i++) {
            POST p = get_post(c, get_list(ll, i));
            printf("%ld - %s\n", get_post_id(p), get_title(p));
        }
    }
    // Query 8
    printf("Query 8:\n");
    Date d3;
    LONG_list l8 = contains_word(c, "Java", 20);
    if (l8 != NULL) {
        for (i = 0; i < get_list_size(l8); i++) {
            long post_id = get_list(l8, i);
            if (post_id == -1) {
                printf("No more posts.\n");
                break;
            }
            POST p = get_post(c, post_id);
            d3 = get_CreationDate(p);
            printf("%ld - %d/%d/%d\n", get_post_id(p), get_day(d3), get_month(d3), get_year(d3));
        }
    }
    
    // Query 9
    printf("Query 9:\n");
    LONG_list l9 = both_participated(c, 29, 7, 20);
    if (l9 != NULL) {
        for (i = 0; i < get_list_size(l9); i++) {
            long post_id = get_list(l9, i);
            if (post_id == -1) {
                printf("No more posts.\n");
                break;
            }
            POST p = get_post(c, post_id);
            Date d4 = get_CreationDate(p);
            printf("%ld - %d/%d/%d\n", get_post_id(p), get_day(d4), get_month(d4), get_year(d4));
        }
    }

    // Query 10
    printf("Query 10:\n");
    long answer = -1;
    answer = better_answer(c, 2);
    if (answer == -1) {
        printf("%s\n", "Não existem respostas para esta pergunta");
    } else { 
        printf("%li\n", answer);
    }

    // Query 11
    printf("Query 11:\n");
    LONG_list l11 = most_used_best_rep(c, 100, d1, d2);
    if (l11 != NULL) {
        for (i = 0; i < get_list_size(l11); i++) {
            long tag_id = get_list(l11, i);
            if (tag_id <= 0) {
                printf("No more tags.\n");
                break;
            }
            TAG t = get_tag_from_id(c, tag_id);
            printf("%ld - %s\n", get_tag_id(t), get_tagName(t));
        }
    }

    clean(c);

    return 0;
}

/**
@file main.c
Função main() do programa.
*/

#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <stdlib.h>
#include <time.h>
#include "pair.h"
#include "list.h"
#include "date.h"
#include "community.h"

/**
\brief Macro para contar o tempo
*/
#define TIME(B) \
    start_time = clock(); \
    B \
    end_time = clock(); \
    elapsed = (end_time - start_time) / (double)CLOCKS_PER_SEC * 1000; \
    printf("elapsed: %lf ms\n", elapsed);

/**
\brief Função main do programa.
@returns Sucesso da função main.
*/
int main(int argc, char *argv[]) {
    long start_time, end_time;
    double elapsed;
    int i;
    if (argc < 2) {
        perror("Missing argument");
        return -1;
    }
    TAD_community c = init();

    TIME(
        load(c, argv[1]);
    )


    // query 1
    printf("Query 1:\n");
    TIME(
        STR_pair pair = info_from_post(c, 801049);
        if (pair) {
            char *fst = get_fst_str(pair);
            char *snd = get_snd_str(pair);
            printf("%s %s\n", fst, snd);
            free(fst);
            free(snd);
        }
        free_str_pair(pair);
    )

    // Query 2
    printf("Query 2:\n");
    TIME(
        LONG_list most_active = top_most_active(c, 10);
        for (i = 0; i < 10; i++) {
            USER u = get_user(c, get_list(most_active, i));
            char *display_name = get_display_name(u);
            printf("%s - %d\n", display_name, get_post_count(u));
            free(display_name);
        }
        free_list(most_active);
    )

    // Query 3
    printf("Query 3:\n");
    Date d1 = createDate(1, 7, 2016);
    Date d2 = createDate(31, 7, 2016);
    TIME(
        LONG_pair l = total_posts(c, d1, d2);
        printf("%li %li\n", get_fst_long(l), get_snd_long(l));
        free_long_pair(l);
    )
    free_date(d1);
    free_date(d2);

    // Query 4
    printf("Query 4:\n");
    Date d5 = createDate(1, 3, 2013);
    Date d6 = createDate(31, 3, 2013);
    TIME(
        LONG_list ll = questions_with_tag(c, "package-management", d5, d6);
        if (ll != NULL) {           // mais que 0 elementos
            for (i = 0; i < get_list_size(ll); i++) {
                POST p = get_post(c, get_list(ll, i));
                printf("%ld - %s\n", get_post_id(p), get_title(p));
            }
        }
    )
    free_date(d5);
    free_date(d6);

    // Query 5
    printf("Query 5:\n");
    TIME(
        USER u2 = get_user_info(c, 314961);
        char *bio = get_bio(u2);
        printf("%ld - %s\n", get_id(u2), bio);
        free(bio);
        free_user(u2);
    )

    // Query 6
    printf("Query 6:\n");
    Date d7 = createDate(1, 11, 2015);
    Date d8 = createDate(30, 11, 2015);
    TIME(
        ll = most_voted_answers(c, 5, d7, d8);
        if (ll != NULL) {           // mais que 0 elementos
            for (i = 0; i < get_list_size(ll); i++) {
                POST p = get_post(c, get_list(ll, i));
                printf("%ld - %ld\n", get_post_id(p), get_score(p));
            }
            free_list(ll);
        }
    )
    free_date(d7);
    free_date(d8);

    // Query 7
    printf("Query 7:\n");
    Date d9 = createDate(1, 8, 2014);
    Date d10 = createDate(11, 8, 2014);
    TIME(
        ll = most_answered_questions(c, 10, d9, d10);
        if (ll != NULL) {           // mais que 0 elementos
            for (i = 0; i < get_list_size(ll); i++) {
                POST p = get_post(c, get_list(ll, i));
                char *title = get_title(p);
                printf("%ld - %s\n", get_post_id(p), title);
                free(title);
            }
        }
        free_list(ll);
    )
    free_date(d9);
    free_date(d10);

    // Query 8
    printf("Query 8:\n");
    Date d3 = NULL;
    TIME(
        LONG_list l8 = contains_word(c, "kde", 10);
        if (l8 != NULL) {
            for (i = 0; i < get_list_size(l8); i++) {
                long post_id = get_list(l8, i);
                if (post_id == -1) {
                    printf("No more posts.\n");
                    break;
                }
                POST p = get_post(c, post_id);
                d3 = get_date(p);
                printf("%ld - %d/%d/%d\n", get_post_id(p), get_day(d3), get_month(d3), get_year(d3));
            }
        }
        free_list(l8);
    )
    if (d3) free_date(d3);

    // Query 9
    printf("Query 9:\n");
    TIME(
        Date d4 = NULL;
        LONG_list l9 = both_participated(c, 87, 5691, 10);
        if (l9 != NULL) {
            for (i = 0; i < get_list_size(l9); i++) {
                long post_id = get_list(l9, i);
                if (post_id == -1) {
                    printf("No more posts.\n");
                    break;
                }
                POST p = get_post(c, post_id);
                d4 = get_date(p);
                printf("%ld - %d/%d/%d\n", get_post_id(p), get_day(d4), get_month(d4), get_year(d4));
            }
        }
        free_list(l9);
    )
    if (d4) free_date(d4);

    // Query 10
    printf("Query 10:\n");
    TIME(
        long answer = -1;
        answer = better_answer(c, 30334);
        if (answer == -1) {
            printf("%s\n", "Não existem respostas para esta pergunta");
        } else {
            printf("%li\n", answer);
        }
    )

    // Query 11
    printf("Query 11:\n");
    Date d11 = createDate(1, 11, 2013);
    Date d12 = createDate(30, 11, 2013);
    TIME(
        LONG_list l11 = most_used_best_rep(c, 5, d11, d12);
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
        free_list(l11);
    )
    free_date(d11);
    free_date(d12);

    clean(c);

    return 0;
}

#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <stdlib.h>
#include "pair.h"
#include "list.h"
#include "date.h"
#include "community.h"

int main(int argc, char *argv[])
{
    int i;
    if (argc < 2) {
        perror("Missing argument");
        return -1;
    }
    TAD_community c = init();
    load(c, argv[1]);
    printf("Query 1:\n");
    for (i = 1; i < 20; i++) {
        // query 1
        STR_pair pair = info_from_post(c, i);
        if (pair)
            printf("%s %s\n", get_fst_str(pair), get_snd_str(pair));
    }

    printf("Query 2:\n");
    // Query 2
    LONG_list most_active = top_most_active(c, 15);
    for (i = 0; i < 15; i++) {
        USER u = get_user(c, get_list(most_active, i));
        printf("%s - %d\n", get_display_name(u), get_post_count(u));
    }

    printf("Query 3:\n");
    // Query 3
    Date d1 = createDate(1, 1, 2000);
    Date d2 = createDate(1, 1, 2028);

    LONG_pair l;
    l = (total_posts(c, d1, d2));
    printf("%li %li\n", get_fst_long(l), get_snd_long(l));

    printf("Query 4:\n");
    // Query 4
    LONG_list ll = questions_with_tag(c, "ai", d1, d2);
    if (ll != NULL) {           // mais que 0 elementos
        for (i = 0; i < get_list_size(ll); i++) {
            POST p = get_post(c, get_list(ll, i));
            printf("%ld - %s\n", get_post_id(p), get_title(p));
        }
    }
    printf("Query 5:\n");

    printf("Query 6:\n");
    // Query 6
    ll = most_voted_answers(c, 15, d1, d2);
    if (ll != NULL) {           // mais que 0 elementos
        for (i = 0; i < get_list_size(ll); i++) {
            POST p = get_post(c, get_list(ll, i));
            printf("%ld - %ld\n", get_post_id(p), get_score(p));
        }
    }

    printf("Query 7:\n");
    // Query 7
    ll = most_answered_questions(c, 15, d1, d2);
    if (ll != NULL) {           // mais que 0 elementos
        for (i = 0; i < get_list_size(ll); i++) {
            POST p = get_post(c, get_list(ll, i));
            printf("%ld - %s\n", get_post_id(p), get_title(p));
        }
    }
    return 0;
}

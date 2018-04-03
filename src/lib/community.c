#include <stdio.h>
#include <stdlib.h>
#include <math.h>               // floor, log10
#include <libxml/hash.h>
#include <string.h>
#include <assert.h>
#include "user.h"
#include "pair.h"
#include "list.h"
#include "linked_list.h"
#include "post.h"
#include "tag.h"
#include "date.h"
#include "common.h"
#include "community.h"

enum {
    INIT_USERS = 10,
    INIT_POSTS = 10,
    INIT_TAGS = 10,
};

struct TCD_community {
    xmlHashTable *users;
    LINKED_LIST user_list;
    xmlHashTable *tags_from_id;
    xmlHashTable *tags_from_name;
    xmlHashTable *posts;
    LINKED_LIST post_list;
};

TAD_community init_community() {
    TAD_community new = malloc(sizeof(struct TCD_community));
    new->users = xmlHashCreate(INIT_USERS);
    new->user_list = init_linked_list();
    new->posts = xmlHashCreate(INIT_POSTS);
    new->post_list = init_linked_list();
    new->tags_from_id = xmlHashCreate(INIT_TAGS);
    new->tags_from_name = xmlHashCreate(INIT_TAGS);
    return new;
}

void add_user(TAD_community com, USER user) {
    xmlHashAddEntry(com->users, (const xmlChar *)ltoa(get_id(user)), user);
    com->user_list = add(com->user_list, user);
}

void add_tag(TAD_community com, TAG tag) {
    xmlHashAddEntry(com->tags_from_id, (const xmlChar *)ltoa(get_tag_id(tag)), tag);
    xmlHashAddEntry(com->tags_from_name, (const xmlChar *)get_tagName(tag), tag);
}

void insert_by_date(TAD_community com, LONG_list l, POST p, int n, int max_n);

void add_post(TAD_community com, POST post) {
    LONG_list l;
    int user_id = get_user_id(post);
    if (user_id > 0) {
        USER u = (USER)xmlHashLookup(com->users, (const xmlChar *)itoa(user_id));

        // Adicionar post aos 10 últimos posts
        l = get_posts_long_list(u);
        insert_by_date(com, l, post, MIN2(get_post_count(u), 10), 10);
        set_post_list(u, l);

        set_post_count(u, get_post_count(u) + 1);

        // Se for resposta, adicionar à lista de respostas da respetiva pergunta
        if (get_type(post) == ANSWER) {
            POST parent_post = get_post(com, get_parent_id(post));
            if (parent_post) {
                add_answer(parent_post, get_post_id(post));
            }
            // TODO: lidar com posts cujas respetivas questões têm um id maior que o próprio, o que significa que não estão na hash table ainda.
        }
    }
    xmlHashAddEntry(com->posts, (const xmlChar *)itoa(get_post_id(post)), post);
    com->post_list = add(com->post_list, post);
}

USER get_user(TAD_community com, long id) {
    return xmlHashLookup(com->users, (const xmlChar *)ltoa(id));
}

POST get_post(TAD_community com, long id) {
    return xmlHashLookup(com->posts, (const xmlChar *)ltoa(id));
}

TAG get_tag_from_id(TAD_community com, long id) {
    return xmlHashLookup(com->tags_from_id, (const xmlChar *)ltoa(id));
}

TAG get_tag_from_name(TAD_community com, char *name) {
    return xmlHashLookup(com->tags_from_name, (const xmlChar *)name);
}

char *get_author_name(TAD_community com, POST p) {
    long id = get_user_id(p); // TODO: converter todos os ids para long
    if (id == -1) {
        return get_user_display_name(p);
    } else {
        USER u = (USER)xmlHashLookup(com->users, (const xmlChar *)ltoa(id));
        return get_display_name(u);
    }
}

char *get_question_title(TAD_community com, POST p) {
    char *title = get_title(p);
    if (title == NULL) {
        int parentId = (int)(get_parent_id(p));
        POST p = (POST)xmlHashLookup(com->posts, (const xmlChar *)itoa(parentId));
        title = get_title(p);
    }
    return title;
}

/* Interrogação 1: Dado o identificador de um post, a função deve retor-
 * nar o tı́tulo do post e o nome (não o ID) de utilizador do autor. Se o post
 * for uma resposta, a função deverá retornar informações (tı́tulo e utilizador)
 * da pergunta correspondente;
 */
STR_pair info_from_post(TAD_community com, long id) {
    POST p = (POST)xmlHashLookup(com->posts, (const xmlChar *)ltoa(id));
    if (p == NULL)      // TODO: fazer logging de erros (post == NULL, user == NULL, etc.)
        return NULL;
    STR_pair pair = create_str_pair(get_question_title(com, p), get_author_name(com, p));
    return pair;
}

/* Interrogação 2: Pretende obter o top N utilizadores com maior número
 * de posts de sempre. Para isto, devem ser considerados tanto perguntas
 * quanto respostas dadas pelo respectivo utilizador;
 */

void insert_by_post_count(TAD_community com, LONG_list l, USER u, int n, int max_n);

LONG_list top_most_active(TAD_community com, int N) {
    LONG_list list = create_list(N);    //TODO: melhorar nomes das variáveis
    LINKED_LIST l = com->user_list;
    USER u;
    int n = 0;
    while (next(l) != NULL) {
        u = (USER)get_data(l);
        insert_by_post_count(com, list, u, MIN2(n, N), N);
        l = next(l);
        n++;
    }
    return list;
}

void insert_by_post_count(TAD_community com, LONG_list l, USER u, int n, int max_n) {
    int i;
    int post_count = get_post_count(u);
    USER u2;
    for (i = 0; i < n; i++) {
        u2 = (USER)xmlHashLookup(com->users, (const xmlChar *)ltoa(get_list(l, i)));
        if (get_post_count(u2) < post_count) {
            break;
        }
    }
    if (i < max_n)
        push_insert(l, i, get_id(u));
}

/* Interrogação 3: Dado um intervalo de tempo arbitrário, obter o número
 * total de posts (identificando perguntas e respostas separadamente) neste
 * perı́odo;
 */

LONG_pair total_posts(TAD_community com, Date begin, Date end) {
    long questions = 0;
    long answers = 0;
    LONG_pair l = create_long_pair(questions, answers);
    LINKED_LIST x = com->post_list;
    POST p;

    while (next(x)) {
        p = (POST)get_data(x);
        if ((isAfter(get_CreationDate(p), begin))
            && (isBefore(get_CreationDate(p), end))) {
            if (get_type(p) == QUESTION) {
                questions++;
            } else {
                answers++;
            }
        }
        x = next(x);
    }

    set_fst_long(l, questions);
    set_snd_long(l, answers);
    return l;
}

/* Interrogação 4: Dado um intervalo de tempo arbitrário, retornar todas
 * as perguntas contendo uma determinada tag. O retorno da função deverá ser
 * uma lista com os IDs das perguntas ordenadas em cronologia inversa.
 */

LONG_list questions_with_tag(TAD_community com, char *tag_name, Date begin, Date end) {
    LINKED_LIST l = init_linked_list();
    LINKED_LIST x = com->post_list;
    POST p;
    int post_count = 0;
    TAG tag = get_tag_from_name(com, tag_name);
    if (tag == NULL)
        return NULL;
    long tag_id = get_tag_id(tag);

    while (next(x)) {
        p = (POST)get_data(x);
        if ((isAfter(get_CreationDate(p), begin))
            && (isBefore(get_CreationDate(p), end))) {
            if (get_type(p) == QUESTION && has_tag(p, tag_id)) {
                l = add(l, p);
                post_count++;
            }
        }
        x = next(x);
    }

    LONG_list r = create_list(post_count);
    int n = 0;
    while (next(l) != NULL) {
        p = (POST)get_data(l);
        insert_by_date(com, r, p, MIN2(n, post_count), post_count);
        l = next(l);
        n++;
    }
    return r;
}

void insert_by_date(TAD_community com, LONG_list l, POST p, int n, int max_n) {
    int i;
    Date post_date = get_CreationDate(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = (POST)xmlHashLookup(com->posts, (const xmlChar *)ltoa(get_list(l, i)));
        if (isBefore(get_CreationDate(p2), post_date)) {
            break;
        }
    }
    if (i < max_n)
        push_insert(l, i, get_post_id(p));
}

/* Interrogação 5: Dado um ID de utilizador, devolver a informação do
 * seu perfil (short bio) e os IDs dos seus 10 últimos posts (perguntas ou res-
 * postas), ordenados por cronologia inversa;
 */
USER get_user_info(TAD_community com, long id) {
    USER user;
    char *bio;
    LONG_list l;

    USER u = get_user(com, id);
    if (u == NULL)
        return NULL;

    bio = get_bio(u);
    l = get_posts_long_list(u);

    user = create_user(id, "", 0, bio, NULL);
    set_post_list(user, l);

    return user;
}

/* Interrogação 6: Dado um intervalo de tempo arbitrário, devolver os IDs
 * das N respostas com mais votos, em ordem decrescente do número de votos; */

void insert_by_score(TAD_community com, LONG_list l, POST p, int n, int max_n);

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end) {
    LONG_list list = create_list(N);
    LINKED_LIST l = com->post_list;
    POST p;
    int n = 0;
    while (next(l) != NULL) {
        p = (POST)get_data(l);
        insert_by_score(com, list, p, MIN2(n, N), N);
        l = next(l);
        n++;
    }
    return list;
}

void insert_by_score(TAD_community com, LONG_list l, POST p, int n, int max_n) {
    int i;
    int post_score = get_score(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = (POST)xmlHashLookup(com->posts, (const xmlChar *)ltoa(get_list(l, i)));
        if (post_score > get_score(p2)) {
            break;
        }
    }
    if (i < max_n)
        push_insert(l, i, get_post_id(p));
}

/* Interrogação 7: Dado um intervalo de tempo arbitrário, devolver as
 * IDs das N perguntas com mais respostas, em ordem decrescente do número
 * de votos; */

void insert_by_answer_count(TAD_community com, LONG_list l, POST p, int n, int max_n);

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
    LONG_list list = create_list(N);
    LINKED_LIST l = com->post_list;
    POST p;
    int n = 0;
    while (next(l) != NULL) {
        p = (POST)get_data(l);
        if (get_type(p) == QUESTION && (isAfter(get_CreationDate(p), begin)) && (isBefore(get_CreationDate(p), end))) {
            insert_by_answer_count(com, list, p, MIN2(n, N), N);
            n++;
        }
        l = next(l);
    }
    return list;
}

void insert_by_answer_count(TAD_community com, LONG_list l, POST p, int n, int max_n) {
    int i;
    int post_count = get_answer_count(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = (POST)xmlHashLookup(com->posts, (const xmlChar *)ltoa(get_list(l, i)));
        if (get_answer_count(p2) > post_count) {
            break;
        }
    }
    if (i < max_n) {
        push_insert(l, i, get_post_id(p));
    }
}

/* Interrogação 8: Dado uma palavra, devolver uma lista com os IDs de N
 * perguntas cujos títulos a contenham, ordenados por cronologia inversa;
 */

LINKED_LIST separate_title(char *title);

int find_word(LINKED_LIST title, char *word);

LONG_list contains_word(TAD_community com, char *word, int N) {
    LINKED_LIST titulo = init_linked_list();
    LINKED_LIST x = com->post_list;
    LONG_list r = create_list(N);
    int i;
    for (i = 0; i < N; i++)
        set_list(r, i, -1);
    POST p;
    int n = 0;
    while (next(x) != NULL) {
        p = (POST)get_data(x);
        if (get_type(p) == QUESTION) {
            titulo = separate_title(get_title(p));
            if (find_word(titulo, word)) {
                insert_by_date(com, r, p, MIN2(n, N), N);
                n++;
            }
        }
        x = next(x);
    }

    return r;
}

LINKED_LIST separate_title(char *title) {
    int i = 0;
    int r = 0;
    int tam = strlen(title);
    char word[1024];
    LINKED_LIST titulo = init_linked_list();
    while (i <= tam) {
        if (title[i] == ' ' || title[i] == '.' || title[i] == ',' ||
            title[i] == '!' || title[i] == '?' || title[i] == ';' || title[i] == ';' || title[i] == ':' || title[i] == '\0') {
            word[r] = '\0';
            titulo = add(titulo, mystrdup(word));
            i++;
            r = 0;
        } else {
            word[r] = title[i];
            r++;
            i++;
        }
    }
    return titulo;
}

int find_word(LINKED_LIST title, char *word) {
    char *titulo;
    while (next(title)) {
        titulo = get_data(title);
        if (strcmp(titulo, word) == 0) {
            return 1;
        } else {
            title = next(title);
        }
    }
    return 0;
}

/* Interrogação 9: Dados os IDs de dois utilizadores, devolver as últimas
 * N perguntas (cronologia inversa) em que participaram dois utilizadores es-
 * pecı́ficos. Note que os utilizadores podem ter participado via pergunta ou
 * respostas; */

int both_users_participate(TAD_community com, POST p, long id1, long id2);

LONG_list both_participated(TAD_community com, long id1, long id2, int N) {
    LINKED_LIST x = com->post_list;
    POST p;
    LONG_list r = create_list(N);
    int i;
    for (i = 0; i < N; i++)
        set_list(r, i, -1);
    int n = 0;
    while (next(x)) {
        p = (POST)get_data(x);
        if (get_type(p) == QUESTION && both_users_participate(com, p, id1, id2)) {
            insert_by_date(com, r, p, MIN2(n, N), N);
            n++;
        }
        x = next(x);
    }
    return r;
}

int both_users_participate(TAD_community com, POST p, long id1, long id2) {
    assert(get_type(p) == QUESTION);
    int i, answer_count;
    POST p2;
    int match_id1 = 0, match_id2 = 0;
    long question_user_id = get_user_id(p);
    if (question_user_id == id1)
        match_id1 = 1;
    if (question_user_id == id2)
        match_id2 = 1;
    LONG_list answer_ids = get_answers(p);
    answer_count = get_answer_count(p);
    for (i = 0; i < answer_count; i++) {
        long post_id = get_list(answer_ids, i);
        if (post_id < 0)        // Nem todas as questões estão a ser introduzidas na lista, assim os ids não são de nenhum utilizador.
            continue;
        p2 = (POST)xmlHashLookup(com->posts, (const xmlChar *)ltoa(post_id));
        if (p2 != NULL) {
            int user_id = get_user_id(p2);
            if (user_id == id1)
                match_id1 = 1;
            if (user_id == id2)
                match_id2 = 1;
        }
    }
    return match_id1 && match_id2;
}

/* Interrogação 11: Dado um intervalo arbitrário de tempo, devolver os
 * identificadores das N tags mais usadas pelos N utilizadores com melhor re-
 * putação. Em ordem decrescente do número de vezes em que a tag foi usada. */

LONG_list best_rep_users(TAD_community com, int N);

void insert_by_rep(TAD_community com, LONG_list l, USER u, int n, int max_n);

LONG_list most_used_tags(TAD_community com, int N, LONG_list best_rep, Date begin, Date end);

int posted_by_users(POST p, int N, LONG_list best_rep);

typedef struct tag_count {
    long id;
    char *name;
    int count;
} *TAG_COUNT;

void insert_by_tag_count(xmlHashTable *tag_count_hash, LONG_list l, TAG_COUNT t, int n, int max_n);

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end) {
    LONG_list best_rep = best_rep_users(com, N);
    LONG_list most_used = most_used_tags(com, N, best_rep, begin, end);
    return most_used;
}

LONG_list best_rep_users(TAD_community com, int N) {
    LONG_list result = create_list(N);
    LINKED_LIST l = com->user_list;
    int n = 0;
    while (next(l)) {
        USER u = get_data(l);
        insert_by_rep(com, result, u, MIN2(n, N), N);
        n++;
        l = next(l);
    }
    return result;
}

void insert_by_rep(TAD_community com, LONG_list l, USER u, int n, int max_n) {
    int i;
    int rep = get_rep(u);
    USER u2;
    for (i = 0; i < n; i++) {
        u2 = get_user(com, get_list(l, i));
        if (get_rep(u2) > rep) {
            break;
        }
    }
    if (i < max_n) {
        push_insert(l, i, get_id(u));
    }
}

LONG_list most_used_tags(TAD_community com, int N, LONG_list best_rep, Date begin, Date end) {
    LINKED_LIST l = com->post_list;
    xmlHashTable *tag_count_hash = xmlHashCreate(INIT_TAGS);
    LINKED_LIST tag_count_list = init_linked_list();
    int i;

    // Contar tags
    while (next(l)) {
        POST p = get_data(l);
        Date creation_date = get_CreationDate(p);
        if (is_between(creation_date, begin, end) && posted_by_users(p, N, best_rep)) {
            int ntags = get_ntags(p);
            LONG_list tags = get_tags(p);
            TAG_COUNT t;
            for (i = 0; i < ntags; i++) {
                t = (TAG_COUNT)xmlHashLookup(tag_count_hash, (const xmlChar *)ltoa(get_list(tags, i)));
                if (t == NULL) {
                    t = malloc(sizeof(struct tag_count));
                    t->id = get_list(tags, i);
                    t->name = mystrdup(get_tagName(get_tag_from_id(com, get_list(tags, i))));
                    t->count = 0;
                    xmlHashAddEntry(tag_count_hash, (const xmlChar *)ltoa(get_list(tags, i)), t);
                    tag_count_list = add(tag_count_list, t);
                }
                t->count++;
            }
        }
        l = next(l);
    }

    // Inserir por ordem
    int n = 0;
    LONG_list r = create_list(N);
    for (i = 0; i < N; i++)
        set_list(r, i, -1);
    while (next(tag_count_list)) {
        TAG_COUNT t = get_data(tag_count_list);
        insert_by_tag_count(tag_count_hash, r, t, MIN2(n, N), N);
        n++;
        tag_count_list = next(tag_count_list);
    }

    return r;
}

int posted_by_users(POST p, int N, LONG_list best_rep) {
    long user_id = get_user_id(p);
    int i;
    for (i = 0; i < N; i++) {
        if (user_id == get_list(best_rep, i)) {
            return 1;
        }
    }
    return 0;
}

void insert_by_tag_count(xmlHashTable *tag_count_hash, LONG_list l, TAG_COUNT t, int n, int max_n) {
    int i;
    int count = t->count;
    TAG_COUNT t2;
    for (i = 0; i < n; i++) {
        t2 = xmlHashLookup(tag_count_hash, (const xmlChar *)ltoa(get_list(l, i)));
        if (t2->count > count) {
            break;
        }
    }
    if (i < max_n) {
        push_insert(l, i, t->id);
    }
}

TAD_community clean_community(TAD_community com) {
    free_linked_list(com->user_list);
    free_linked_list(com->post_list);
    xmlHashFree(com->users, NULL);
    xmlHashFree(com->tags_from_id, NULL);
    xmlHashFree(com->tags_from_name, NULL);
    xmlHashFree(com->posts, NULL);
    return com;
}

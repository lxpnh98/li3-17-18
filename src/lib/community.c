#include <stdio.h>
#include <stdlib.h>
#include <math.h>               // floor, log10
#include <libxml/hash.h>
#include <string.h>
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
    xmlHashTable *tags;
    xmlHashTable *posts;
    LINKED_LIST post_list;
};

TAD_community init_community()
{
    TAD_community new = malloc(sizeof(struct TCD_community));
    new->users = xmlHashCreate(INIT_USERS);
    new->user_list = init_linked_list();
    new->posts = xmlHashCreate(INIT_POSTS);
    new->post_list = init_linked_list();
    new->tags = xmlHashCreate(INIT_TAGS);
    return new;
}

void add_user(TAD_community com, USER user)
{
    int id_len = floor(log10((double)get_id(user))) + 1;
    char id_str[id_len];
    sprintf(id_str, "%ld", get_id(user));
    xmlHashAddEntry(com->users, (const xmlChar *)id_str, user);
    com->user_list = add(com->user_list, user);
}

void add_tag(TAD_community com, TAG tag)
{
    xmlHashAddEntry(com->tags, (const xmlChar *)get_tagName(tag), tag);
}

void insert_by_date(TAD_community com, LONG_list l, POST p, int n, int max_n);

void add_post(TAD_community com, POST post)
{
    LONG_list l;
    int user_id = get_user_id(post);
    if (user_id > 0) {
        USER u = (USER) xmlHashLookup(com->users, (const xmlChar *)itoa(user_id));
        // Adicionar post aos 10 últimos posts
        l = get_posts_long_list(u);
        insert_by_date(com, l, post, MIN2(get_post_count(u), 10), 10);
        set_post_list(u, l);

        set_post_count(u, get_post_count(u) + 1);

    }
    xmlHashAddEntry(com->posts, (const xmlChar *)itoa(get_post_id(post)), post);
    com->post_list = add(com->post_list, post);
}

USER get_user(TAD_community com, long id)
{
    return xmlHashLookup(com->users, (const xmlChar *)ltoa(id));
}

POST get_post(TAD_community com, long id)
{
    return xmlHashLookup(com->posts, (const xmlChar *)ltoa(id));
}

char *get_author_name(TAD_community com, POST p)
{
    int id = (int)(get_user_id(p)); // TODO: converter todos os ids para long
    if (id == -1) {
        return get_user_display_name(p);
    } else {
        USER u = (USER) xmlHashLookup(com->users, (const xmlChar *)itoa(id));
        return get_display_name(u);
    }
}

char *get_question_title(TAD_community com, POST p)
{
    char *title = get_title(p);
    if (title == NULL) {
        int parentId = (int)(get_parent_id(p));
        POST p = (POST) xmlHashLookup(com->posts, (const xmlChar *)itoa(parentId));
        title = get_title(p);
    }
    return title;
}

/* Interrogação 1: Dado o identificador de um post, a função deve retor-
 * nar o tı́tulo do post e o nome (não o ID) de utilizador do autor. Se o post
 * for uma resposta, a função deverá retornar informações (tı́tulo e utilizador)
 * da pergunta correspondente;
 */
STR_pair info_from_post(TAD_community com, long id)
{
    POST p = (POST) xmlHashLookup(com->posts, (const xmlChar *)ltoa(id));
    if (p == NULL)
        return NULL;
    STR_pair pair = create_str_pair(get_question_title(com, p), get_author_name(com, p));
    return pair;
}

/* Interrogação 2: Pretende obter o top N utilizadores com maior número
 * de posts de sempre. Para isto, devem ser considerados tanto perguntas
 * quanto respostas dadas pelo respectivo utilizador;
 */

void insert_by_post_count(TAD_community com, LONG_list l, USER u, int n, int max_n);

LONG_list top_most_active(TAD_community com, int N)
{
    LONG_list list = create_list(N);    //TODO: melhorar nomes das variáveis
    LINKED_LIST l = com->user_list;
    USER u;
    int n = 0;
    while (next(l) != NULL) {
        u = (USER) get_data(l);
        insert_by_post_count(com, list, u, MIN2(n, N), N);
        l = next(l);
        n++;
    }
    return list;
}

void insert_by_post_count(TAD_community com, LONG_list l, USER u, int n, int max_n)
{
    int i;
    int post_count = get_post_count(u);
    USER u2;
    for (i = 0; i < n; i++) {
        u2 = (USER) xmlHashLookup(com->users, (const xmlChar *)ltoa(get_list(l, i)));
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
LONG_pair total_posts(TAD_community com, Date begin, Date end)
{
    long questions = 0;
    long answers = 0;
    LONG_pair l;
    LINKED_LIST x = com->post_list;
    POST p;

    while (next(x)) {
        p = (POST) get_data(x);
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

LONG_list questions_with_tag(TAD_community com, char *tag, Date begin, Date end)
{
    LINKED_LIST l = init_linked_list();
    LINKED_LIST x = com->post_list;
    POST p;
    int post_count = 0;

    while (next(x)) {
        p = (POST) get_data(x);
        if ((isAfter(get_CreationDate(p), begin))
            && (isBefore(get_CreationDate(p), end))) {
            if (get_type(p) == QUESTION && has_tag(p, tag)) {
                l = add(l, p);
                post_count++;
            }
        }
        x = next(x);
    }

    LONG_list r = create_list(post_count);
    int n = 0;
    while (next(l) != NULL) {
        p = (POST) get_data(l);
        insert_by_date(com, r, p, MIN2(n, post_count), post_count);
        l = next(l);
        n++;
    }
    return r;
}

void insert_by_date(TAD_community com, LONG_list l, POST p, int n, int max_n)
{
    int i;
    Date post_date = get_CreationDate(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = (POST) xmlHashLookup(com->posts, (const xmlChar *)ltoa(get_list(l, i)));
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
USER get_user_info(TAD_community com, long id){
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

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
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

void insert_by_score(TAD_community com, LONG_list l, POST p, int n, int max_n)
{
    int i;
    int post_score = get_score(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = (POST) xmlHashLookup(com->posts, (const xmlChar *)ltoa(get_list(l, i)));
        if (post_score > get_score(p2)) {
            break;
        }
    }
    if (i < max_n)
        push_insert(l, i, get_post_id(p));
}


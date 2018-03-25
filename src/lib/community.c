#include <stdio.h>
#include <stdlib.h>
#include <math.h> // floor, log10
#include <libxml/hash.h>
#include <string.h>
#include "user.h"
#include "pair.h"
#include "list.h"
#include "post.h"
#include "tag.h"
#include "date.h"
#include "community.h"

enum {
    INIT_USERS = 10,
    INIT_POSTS = 10,
    INIT_TAGS  = 10,
};

struct TCD_community {
    xmlHashTable *users;
    xmlHashTable *tags;
    xmlHashTable *posts;
};

TAD_community init_community() {
    TAD_community new = malloc(sizeof(struct TCD_community));
    new->users = xmlHashCreate(INIT_USERS);
    new->posts = xmlHashCreate(INIT_POSTS);
    new->tags  = xmlHashCreate(INIT_TAGS);
    return new;
}

void add_user(TAD_community com, USER user) {
    int id_len = floor(log10((double)get_id(user))) + 1;
    char id_str[id_len];
    sprintf(id_str, "%ld", get_id(user));
    xmlHashAddEntry(com->users, (const xmlChar *)id_str, user);
}

void add_tag(TAD_community com, TAG tag) {
    xmlHashAddEntry(com->tags, (const xmlChar *)get_tagName(tag), tag);
}

void add_post(TAD_community com, POST post) {
    int id_len = floor(log10((double)get_post_id(post))) + 1; //TODO: implementar função para não repetir este código sempre
    char id_str[id_len];
    sprintf(id_str, "%ld", get_post_id(post));
    xmlHashAddEntry(com->posts, (const xmlChar *)id_str, post);
}

char *get_author_name(TAD_community com, POST p) {
    int id = (int)(get_user_id(p)); // TODO: converter todos os ids para long
    if(id == -1) {
        return get_user_display_name(p);
    } else {
        int id_len = floor(log10(id)) + 1;
        char id_str[id_len];
        sprintf(id_str, "%d", id);
        USER u = (USER)xmlHashLookup(com->users, (const xmlChar *)id_str);
        return get_display_name(u);
    }
}

char *get_question_title(TAD_community com, POST p) {
    char *title = get_title(p);
    if(title == NULL) {
        int parentId = (int)(get_parent_id(p));
        int id_len = floor(log10(parentId)) + 1;
        char id_str[id_len];
        sprintf(id_str, "%d", parentId);
        POST p = (POST)xmlHashLookup(com->posts, (const xmlChar *)id_str);
        title = get_title(p);
    }
    return title;
}
/* Interrogação 1: Dado o identificador de um post, a função deve retor-
 * nar o tı́tulo do post e o nome (não o ID) de utilizador do autor. Se o post
 * for uma resposta, a função deverá retornar informações (tı́tulo e utilizador)
 * da pergunta correspondente;
 */
STR_pair info_from_post(TAD_community com, int id) {
    int id_len = floor(log10(id)) + 1;
    char id_str[id_len];
    sprintf(id_str, "%d", id);
    POST p = (POST)xmlHashLookup(com->posts, (const xmlChar *)id_str);
    if (p == NULL) return NULL;
    STR_pair pair = create_str_pair(get_question_title(com, p), get_author_name(com, p));
    return pair;
}

/* Interrogação 2: Pretende obter o top N utilizadores com maior número
 * de posts de sempre. Para isto, devem ser considerados tanto perguntas
 * quanto respostas dadas pelo respectivo utilizador;
 */
LONG_list top_most_active(TAD_community com, int N) {
    LONG_list list = create_list(N);
    return list;
}

/* Interrogação 3: Dado um intervalo de tempo arbitrário, obter o número
 * total de posts (identificando perguntas e respostas separadamente) neste
 * perı́odo;
 */
LONG_pair total_posts(TAD_community com, Date begin, Date end) {
   return 0;
}


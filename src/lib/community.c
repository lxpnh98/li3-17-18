#include <stdio.h>
#include <stdlib.h>
#include <math.h> // floor, log10
#include <libxml/hash.h>
#include <string.h>
#include "user.h"
#include "pair.h"
#include "list.h"
#include "post.h"
#include "community.h"
#include "tag.h"

enum {
    INIT_USERS = 10,
    INIT_POSTS = 10,
    INIT_TAGS  = 10
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
    STR_pair pair = create_str_pair(get_title(p), get_author_name(p));
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


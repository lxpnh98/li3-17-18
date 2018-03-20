#include <stdio.h>
#include <stdlib.h>
#include <math.h> // floor, log10
#include <libxml/hash.h>
#include "user.h"
#include "community.h"

enum {
    INIT_USERS = 10,
    INIT_POSTS = 10,
};

struct TCD_community {
    xmlHashTable *users;
    xmlHashTable *posts;
};

TAD_community init_community() {
    TAD_community new = malloc(sizeof(struct TCD_community));
    new->users = xmlHashCreate(INIT_USERS);
    new->posts = xmlHashCreate(INIT_POSTS);
    return new;
}

void add_user(TAD_community com, USER user) {
    int id_len = floor(log10((double)get_id(user))) + 1;
    char id_str[id_len];
    sprintf(id_str, "%ld", get_id(user));
    xmlHashAddEntry(com->users, (const xmlChar *)id_str, user);
}


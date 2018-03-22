#include <stdio.h>
#include <stdlib.h>
#include <math.h> // floor, log10
#include <libxml/hash.h>
#include <string.h>
#include "user.h"
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


/**
@file user.h
Definição de funções acesso à estrutura de dados USER.
*/

#ifndef __USER__
#define __USER__

#include "list.h"

typedef struct user *USER;

USER create_user(long id, char *display_name, long rep, char *bio, long *post_history);

long get_id(USER u);

char *get_bio(USER u);

long *get_10_latest_posts(USER u);  // caso um utilizador tenha menos de 10 posts, por -1 como padding

long get_rep(USER u);

char *get_display_name(USER u);

int get_post_count(USER u);

LONG_list get_posts_long_list(USER u);

void set_post_count(USER u, int new_count);

void set_bio(USER u, char *bio);

void set_post_list(USER u, LONG_list l);

void free_user(USER u);
void free_userv(void *u);

#endif

#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "list.h"
#include "common.h"

struct user {
    long id;    /** Id do utilizador */
    long rep;   /** Reputação do utilizador */
    char *display_name; /** Nome de ecrãn do utilizador */
    char *bio;      /** Biografia do utilizador */
    long posts[10]; /** Últimos 10 posts do utilizador */
    int post_count; /** Número de posts submetidos */
};

USER create_user(long id, char *display_name, long rep, char *bio, long *post_history)
{
    USER u = malloc(sizeof(struct user));
    u->id = id;
    u->rep = rep;
    u->display_name = mystrdup(display_name);
    u->bio = mystrdup(bio);
    u->post_count = 0;
    //memcpy(u->posts, post_history, sizeof(long) * 10);
    return u;
}

long get_id(USER u)
{
    return u->id;
}

char *get_bio(USER u)
{
    if (u)
        return u->bio;
    return NULL;
}

long *get_10_latest_posts(USER u)
{
    long *r = malloc(sizeof(long) * 10);
    memcpy(r, u->posts, sizeof(long) * 10);
    return r;
}

char *get_display_name(USER u)
{
    return mystrdup(u->display_name);
}

int get_post_count(USER u)
{
    return u->post_count;
}

LONG_list get_posts_long_list(USER u)
{
    int i;
    LONG_list l = create_list(10);
    long *posts = get_10_latest_posts(u);
    for (i = 0; i < 10; i++)
        set_list(l, i, posts[i]);
    return l;
}

void set_post_count(USER u, int new_count)
{
    u->post_count = new_count;
}

void set_bio(USER u, char *bio)
{
    if(u->bio) free(u->bio);
    u->bio = mystrdup(bio);
}

void set_post_list(USER u, LONG_list l)
{
    int i;
    int n = get_list_size(l);
    for (i = 0; i < n; i++)
        u->posts[i] = get_list(l, i);
}

void free_user(USER u)
{
    if (u) {
        free(u->bio);
        free(u);
    }
}

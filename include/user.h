#ifndef __USER__
#define __USER__

typedef struct user *USER;

USER create_user(long id, char *display_name, long rep, char *bio,
                 long *post_history);

char *get_bio(USER u);

long *get_10_latest_posts(USER u);  // caso um utilizador tenha menos de 10 posts, por -1 como padding

long get_id(USER u);

char *get_display_name(USER u);

int get_post_count(USER u);

void set_post_count(USER u, int new_count);

void free_user(USER u);

#endif

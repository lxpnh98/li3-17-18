#ifndef __USER__
#define __USER__
typedef struct user* USER;

USER create_user(long id, char* short_bio, long* post_history);
char* get_bio(USER u);
long* get_10_latest_posts(USER u); // caso um utilizador tenha menos
long get_id(USER u);
                                   // de 10 posts, por -1 como padding
void free_user(USER u);
#endif

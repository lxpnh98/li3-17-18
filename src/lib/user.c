#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "common.h"

struct user {
    long id;            /** Id do utilizador */
    long rep;           /** Reputação do utilizador */
    char* display_name; /** Nome de ecrãn do utilizador */
    char* bio;          /** Biografia do utilizador */
    long posts[10];     /** Últimos 10 posts do utilizador */
};

USER create_user(long id, char *display_name, long rep,  char* bio, long* post_history) {
  USER u = malloc(sizeof(struct user));
  u->id = id;
  u->rep = rep;
  u->display_name = mystrdup(display_name);
  u->bio = mystrdup(bio);
  //memcpy(u->posts, post_history, sizeof(long) * 10);
  return u;
}

long get_id(USER u) {
    return u->id;
}

char* get_bio(USER u) {
  if(u)
    return u->bio;
  return NULL;
}

long* get_10_latest_posts(USER u) {
  long* r = malloc(sizeof(long)*10);
  memcpy(r, u->posts, sizeof(long)*10);
  return r;
}

void free_user(USER u) {
  if(u) {
    free(u->bio);
    free(u);
  }
}

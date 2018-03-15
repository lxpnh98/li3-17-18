#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "common.h"

struct user {
    long id;
    char* bio;
    long posts[10];
};

USER create_user(long id, char* bio, long* post_history) {
  USER u = malloc(sizeof(struct user));
  u->id = id;
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

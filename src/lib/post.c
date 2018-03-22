#include <string.h>
#include <stdlib.h>
#include "post.h"
#include "common.h"

struct post {
    long id;                /** Id do post */
    enum post_type type;    /** Id pergunta = 1; Id resposta = 2*/
    long AcceptedAnswer;    /** Id da resposta aceite; -1 em caso de ser uma pergunta*/
};
//    char* display_name;                       /** Nome de ecrãn do utilizador */
 //   char* bio;                                /** Biografia do utilizador */
   // long posts[10];                           /** Últimos 10 posts do utilizador */


POST create_post(long id, enum post_type type, long AcceptedAnswer) {
  POST p = malloc(sizeof(struct post));
  p->id = id;
  p->type = type;
  p->AcceptedAnswer = AcceptedAnswer;

  //u->display_name = mystrdup(display_name);
  //u->bio = mystrdup(bio);
  //memcpy(u->posts, post_history, sizeof(long) * 10);
  return p;
}
/*
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
*/
/**
@file user.c
Funções que operam sobre os utilizadores.
*/

#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "list.h"
#include "common.h"

/** \brief Estrutura que armazena a informação do utilizador */
struct user {
    /** \brief Id do utilizador */
    long id;
    /** \brief Reputação do utilizador */
    long rep;
    /** \brief Nome de ecrãn do utilizador */
    char *display_name;
    /** \brief Biografia do utilizador */
    char *bio;
    /** \brief Últimos 10 posts do utilizador */
    long posts[10];
    /** \brief Número de posts submetidos */
    int post_count;
};

/**
\brief Função que cria um utilizador.
@param id Id do utilizador.
@param display_name String do nome do utilizador.
@param rep Reputação do utilizador.
@param bio Biografia do utilizador.
@param post_history Histórico dos ids dos posts do utilizador.
@returns USER Utilizador.
*/
USER create_user(long id, char *display_name, long rep, char *bio, long *post_history) {
    USER u = malloc(sizeof(struct user));
    u->id = id;
    u->rep = rep;
    u->display_name = mystrdup(display_name);
    u->bio = mystrdup(bio);
    u->post_count = 0;
    //memcpy(u->posts, post_history, sizeof(long) * 10);
    return u;
}

/**
\brief Função que devolve o id de um utilizador.
@param u Estrutura do tipo utilizador.
@returns long Id do utilizador.
*/
long get_id(USER u) {
    return u->id;
}

/**
\brief Função que devolve a biografia de um utilizador.
@param u Estrutura do tipo utilizador.
@returns char* String da biografia do utilizador.
*/
char *get_bio(USER u) {
    if (u)
        return mystrdup(u->bio);
    return NULL;
}

/**
\brief Função que devolve os ids dos 10 últimos posts de um utilizador.
@param u Estrutura do tipo utilizador.
@returns long Ids dos 10 últimos pots do utilizador.
*/
long *get_10_latest_posts(USER u) {
    long *r = malloc(sizeof(long) * 10);
    memcpy(r, u->posts, sizeof(long) * 10);
    return r;
}

/**
\brief Função que devolve a reputação de um utilizador.
@param u Estrutura do tipo utilizador.
@returns long Reputação do utilizador.
*/
long get_rep(USER u) {
    return u->rep;
}

/**
\brief Função que devolve o nome de um utilizador.
@param u Estrutura do tipo utilizador.
@returns char* String do nome do utilizador.
*/
char *get_display_name(USER u) {
    return mystrdup(u->display_name);
}

/**
\brief Função que devolve o número de posts submetidos por um utilizador.
@param u Estrutura do tipo utilizador.
@returns int Número de posts submetidos pelo utilizador.
*/
int get_post_count(USER u) {
    return u->post_count;
}

/**
\brief Função que devolve a lista dos últimos posts submetidos por um utilizador.
@param u Estrutura do tipo utilizador.
@returns LONG_list Lista dos últimos posts submetidos pelo utilizador.
*/
LONG_list get_posts_long_list(USER u) {
    int i;
    LONG_list l = create_list(10);
    long *posts = get_10_latest_posts(u);
    for (i = 0; i < 10; i++)
        set_list(l, i, posts[i]);
    return l;
}

/**
\brief Função que atualiza o número de posts submetidos por um utilizador.
@param u Estrutura do tipo utilizador.
@param new_count Novo número de posts.
*/
void set_post_count(USER u, int new_count) {
    u->post_count = new_count;
}

/**
\brief Função que atualiza a biografia de um utilizador.
@param u Estrutura do tipo utilizador.
@param bio Nova biografia do utilizador.
*/
void set_bio(USER u, char *bio) {
    if (u->bio)
        free(u->bio);
    u->bio = mystrdup(bio);
}

/**
\brief Função que atualiza a lista dos últimos 10 posts submetidos por um utilizador.
@param u Estrutura do tipo utilizador.
@param l Nova lista de posts.
*/
void set_post_list(USER u, LONG_list l) {
    int i;
    int n = get_list_size(l);
    for (i = 0; i < n; i++)
        u->posts[i] = get_list(l, i);
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param u Estrutura do tipo utilizador.
*/
void free_user(USER u) {
    if (u) {
        free(u->bio);
        free(u);
    }
}

void free_userv(void *u) {
    free_user((USER)u);
}

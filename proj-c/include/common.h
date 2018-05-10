/**
@file common.h
Funções e definições de utilidade.
*/

#ifndef __MY_COMMON__
#define __MY_COMMON__

/**
/brief Máximo entre dois números.
*/
#define MAX2(x,y) ((x)>(y) ? (x) : (y))

/**
/brief Mínimo entre dois números.
*/
#define MIN2(x,y) ((x)<(y) ? (x) : (y))

char *mystrdup(const char *s);

/**
/brief Identificador de tipo de dump.
*/
enum dump_type {
    BADGES,
    COMMENTS,
    POST_HISTORY,
    POST_LINKS,
    POSTS,
    TAGS,
    USERS,
    VOTES,
};

char *make_path(const char *, enum dump_type);

char *itoa(int x);

char *ltoa(long x);

#endif

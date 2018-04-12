/**
@file common.c
Funções e definições de utilidade.
*/

#include <common.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
/brief String do nome do dump.
*/
char *dump_file_name[] = {
    "Badges.xml",
    "Comments.xml",
    "PostHistory.xml",
    "PostLinks.xml",
    "Posts.xml",
    "Tags.xml",
    "Users.xml",
    "Votes.xml",
};

/*
\brief Função que duplica uma dada string.
@param char* String a duplicar.
@returns char* String duplicada.
 */
char *mystrdup(const char *s) {
    if (s == NULL)
        return NULL;
    char *d = malloc(strlen(s) + 1);
    if (d == NULL)
        return NULL;
    strcpy(d, s);
    return d;
}

/*
\brief Função que cria um path completo dado uma diretoria e um tipo de ficheiro de dump. (TODO: ativar JAVADOC_AUTOBRIEF no Doxygen)
@param dir Diretoria.
@param t Tipo de ficheiro de dump (escolhido do enum Dump_type).
@returns char* String com o path completo.
 */
char *make_path(const char *dir, enum dump_type t) {
    int slash = dir[strlen(dir)-1] != '/';
    char *d = dump_file_name[t];
    char *r = malloc(strlen(dir) + slash + strlen(d) + 1);
    if (slash) {
        sprintf(r, "%s/%s", dir, d);
    } else {
        sprintf(r, "%s%s", dir, d);
    }
    return r;
}

/*
\brief Função que retorna a representação de um int num string (em base decimal).
@param x Inteiro.
@returns char* String.
 */
char *itoa(int x) {
    int len = floor(log10((double)x)) + 1;
    char *str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "%d", x);
    return str;
}

/*
\brief Função que retorna a representação de um long num string (em base decimal).
@param x Long.
@returns char* String
 */
char *ltoa(long x) {
    long len = floor(log10((double)x)) + 1;
    char *str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "%ld", x);
    return str;
}

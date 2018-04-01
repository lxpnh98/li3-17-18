#include <common.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

// definido par nao dar warnings ao usar a funcao da GNU
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
 * Função que cria um path completo dado uma diretoria e um tipo de ficheiro de dump. (TODO: ativar JAVADOC_AUTOBRIEF no Doxygen)
 *
 * \param dir diretoria
 *
 * \param t tipo de ficheiro de dump (escolhido do enum Dump_type)
 *
 * \return novo string com o path completo
 */
char *make_path(const char *dir, enum dump_type t) { // TODO: fazer make_path() funcionar com um path sem '/' no fim.
    char *d = dump_file_name[t];
    char *r = malloc(strlen(dir) + strlen(d) + 1);
    sprintf(r, "%s%s", dir, d);
    return r;
}

/*
 * Função que retorna a representação de um int num string (em base decimal)
 */
char *itoa(int x) {
    int len = floor(log10((double)x)) + 1;
    char *str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "%d", x);
    return str;
}

/*
 * Função que retorna a representação de um long num string (em base decimal)
 */
char *ltoa(long x) {
    long len = floor(log10((double)x)) + 1;
    char *str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "%ld", x);
    return str;
}

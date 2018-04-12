/**
@file pair.c
Definição de funções de accesso a estrururas de dados dos tipos STR_pair e LONG_pair.
*/

#include <stdlib.h>
#include <string.h>
#include <common.h>
#include "pair.h"

/** \brief Estrutura que representa um par de strings */
struct str_pair {
	/** \brief Primeira string */
    char *fst;
    /** \brief Segunda string */
    char *snd;
};

/**
\brief Função que cria um par de strings.
@param fst Primeira string do par.
@param snd Segunda string do par.
@returns STR_pair Par de strings.
*/
STR_pair create_str_pair(char *fst, char *snd) {
    STR_pair p = malloc(sizeof(struct str_pair));
    p->fst = mystrdup(fst);
    p->snd = mystrdup(snd);
    return p;
}

/**
\brief Função que atualiza a primeira string de um dado par de strings.
@param pair Estrutura do tipo par de strings.
@param str Nova string.
*/
void set_fst_str(STR_pair pair, char *str) {
    free(pair->fst);
    pair->fst = mystrdup(str);
}

/**
\brief Função que atualiza a segunda string de um dado par de strings.
@param pair Estrutura do tipo par de strings.
@param str Nova string.
*/
void set_snd_str(STR_pair pair, char *str) {
    free(pair->snd);
    pair->snd = mystrdup(str);
}

/**
\brief Função que devolve a primeira string de um dado par de strings.
@param pair Estrutura do tipo par de strings.
@returns char Primeira string do par.
*/
char *get_fst_str(STR_pair pair) {
    return pair ? mystrdup(pair->fst) : NULL;
}

/**
\brief Função que devolve a segunda string de um dado par de strings.
@param pair Estrutura do tipo par de strings.
@returns char* Primeira string do par.
*/
char *get_snd_str(STR_pair pair) {
    return pair ? mystrdup(pair->snd) : NULL;
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param pair Estrutura do tipo par de strings.
*/
void free_str_pair(STR_pair pair) {
    if (pair) {
        free(pair->fst);
        free(pair->snd);
        free(pair);
    }
}

/** \brief Estrutura que representa um par de longs */
struct long_pair {
	/** \brief Primeiro long */
    long fst;
    /** \brief Segundo long */
    long snd;
};

/**
\brief Função que cria um par de longs.
@param fst Primeiro long do par
@param snd Segundo long do par.
@returns LONG_pair Par de longs.
*/
LONG_pair create_long_pair(long fst, long snd) {
    LONG_pair p = malloc(sizeof(struct long_pair));
    p->fst = fst;
    p->snd = snd;
    return p;
}

/**
\brief Função que atualiza o primeiro long de um dado par de longs.
@param pair Estrutura do tipo par de longs.
@param l Novo long.
*/
void set_fst_long(LONG_pair pair, long l) {
    pair->fst = l;
}

/**
\brief Função que atualiza o segundo long de um dado par de longs.
@param pair Estrutura do tipo par de longs.
@param l Novo long.
*/
void set_snd_long(LONG_pair pair, long l) {
    pair->snd = l;
}

/**
\brief Função que devolve o primeiro long de um dado par de longs.
@param pair Estrutura do tipo par de longs.
@returns long Primeiro long do par.
*/
long get_fst_long(LONG_pair pair) {
    return pair->fst;
}

/**
\brief Função que devolve o segundo long de um dado par de longs.
@param pair Estrutura do tipo par de longs.
@returns long Segundo long do par.
*/
long get_snd_long(LONG_pair pair) {
    return pair->snd;
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param pair Estrutura do tipo par de longs.
*/
void free_long_pair(LONG_pair pair) {
    free(pair);
}

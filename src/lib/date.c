/**
@file date.c
Funções que operam sobre datas.
*/

#include <stdlib.h>
#include "date.h"

/** \brief Estrutura que armazena a informação da data */
struct date {
    /** \brief Dia */
    int day;
    /** \brief Mês */
    int month;
    /** \brief Ano */
    int year;
};

/**
\brief Função que cria uma data.
@param day Dia da data.
@param month Mês data.
@param year Ano da data.
@returns Date Data.
*/
Date createDate(int day, int month, int year) {
    Date d = malloc(sizeof(struct date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

/**
\brief Função que devolve o dia de uma dada data.
@param d Estrutura do tipo data.
@returns int Dia da data.
*/
int get_day(Date d) {
    return d->day;
}

/**
\brief Função que devolve o mês de uma dada data.
@param d Estrutura do tipo data.
@returns int Mês da data.
*/
int get_month(Date d) {
    return d->month;            //change to enum? (Acho que sim. Desta forma já garantimos a limitação necessária)
}

/**
\brief Função que devolve o ano de uma dada data.
@param d Estrutura do tipo data.
@returns int Ano da data.
*/
int get_year(Date d) {
    return d->year;
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param d Estrutura do tipo data.
*/
void free_date(Date d) {
    free(d);
}

/**
\brief Função que devolve uma cópia de uma dada data.
@param d Estrutura do tipo data.
@returns Date Cópia da data.
*/
Date cloneDate(Date d) {        // TODO: tornar nomes de funções e campos consistentes (sempre 'com_underscores')
    Date c = malloc(sizeof(struct date));
    c->year = get_year(d);
    c->month = get_month(d);
    c->day = get_day(d);
    return c;
}

/**
\brief Função que verifica se uma data d1 ocorre depois da data d2.
@param d1 Estrutura do tipo data.
@param d2 Estrutura do tipo data.
@returns int Inteiro com valor boleano.
*/
int isAfter(Date d1, Date d2) {
    int r = 1;

    if (get_year(d1) < get_year(d2))
        return 0;
    if (get_year(d1) > get_year(d2))
        return 1;
    else {
        if (get_month(d1) < get_month(d2))
            return 0;
        if (get_month(d1) > get_month(d2))
            return 1;
        else {
            if (get_day(d1) < get_day(d2))
                return 0;
            if (get_day(d1) > get_day(d2))
                return 1;
        }
    }
    return r;
}

/**
\brief Função que verifica se uma data d1 ocorre antes da data d2.
@param d1 Estrutura do tipo data.
@param d2 Estrutura do tipo data.
@returns int Inteiro com valor boleano.
*/
int isBefore(Date d1, Date d2) {
    int r = 1;

    if (get_year(d1) > get_year(d2))
        return 0;
    if (get_year(d1) < get_year(d2))
        return 1;
    else {
        if (get_month(d1) > get_month(d2))
            return 0;
        if (get_month(d1) < get_month(d2))
            return 1;
        else {
            if (get_day(d1) > get_day(d2))
                return 0;
            if (get_day(d1) < get_day(d2))
                return 1;
        }
    }
    return r;
}

/**
\brief Função que verifica se uma dada data ocorre entre duas outras datas.
@param d Estrutura do tipo data.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns int Inteiro com valor boleano.
*/
int is_between(Date d, Date begin, Date end) {
    return isAfter(d, begin) && isBefore(d, end);   // TODO: substituir todas as ocorrências destas condições por esta função
}

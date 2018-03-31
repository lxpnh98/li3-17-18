#include <stdlib.h>
#include "date.h"

struct date {
    int day;
    int month;
    int year;
};

Date createDate(int day, int month, int year) {
    Date d = malloc(sizeof(struct date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

int get_day(Date d) {
    return d->day;
}

int get_month(Date d) {
    return d->month;            //change to enum? (Acho que sim. Desta forma já garantimos a limitação necessária)
}

int get_year(Date d) {
    return d->year;
}

void free_date(Date d) {
    free(d);
}

Date cloneDate(Date d) {
    Date c = malloc(sizeof(struct date));
    c->year = get_year(d);
    c->month = get_month(d);
    c->day = get_day(d);
    return c;
}

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

int is_between(Date d, Date begin, Date end) {
    return isAfter(d, begin) && isBefore(d, end);   // TODO: substituir todas as ocorrências destas condições por esta função
}

#ifndef __DATE_H_
#define __DATE_H_

typedef struct date *Date;

Date createDate(int day, int month, int year);

int get_day(Date d);

int get_month(Date d);          // must return a value between 0 and 11

int get_year(Date d);

void free_date(Date d);

Date cloneDate(Date d);

int isBefore(Date d1, Date d2);

int isAfter(Date d1, Date d2);

int is_between(Date d, Date begin, Date end);

#endif

#include <date.h>
#include <stdio.h>
#include <interface.h>

int main(){
    Date d = createDate(1,2,2017);
    printf("Dia: %i\n", get_day(d));

    TAD_community c = init();
    load(c, "../../libxml/");

    return 0;
}

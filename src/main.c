#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <stdlib.h>
#include "pair.h"

int main(int argc, char *argv[]){
    if(argc < 2){
    	perror("Missing argument");
    	return -1;
    }
    TAD_community c = init();
    load(c, argv[1]);
    for (int i=1; i < 20; i++) {
        // query 1
        STR_pair pair = info_from_post(c, i);
        if (pair) printf("%s %s\n", get_fst_str(pair), get_snd_str(pair));
    }

    return 0;
}

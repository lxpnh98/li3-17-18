#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    TAD_community c = init();
    if(argc < 2){
    	perror("Missing argument");
    	return -1;
    }
    load(c, argv[1]);

    return 0;
}

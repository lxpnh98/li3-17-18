#include <string.h>
#include <stdlib.h>
#include "tag.h"
#include "common.h"

// O Id das tags não está na struct porque ele n é necessário nas querries;
struct tag { 
	char* tagName;
};

TAG create_tag(char* tagName){
	TAG t = malloc(sizeof(struct tag));
	t->tagName = mystrdup(tagName);

	return t;
}

char* get_tagName(TAG t){
	if (t)
		return t->tagName;
	return NULL;
}

void free_tag(TAG t){
	if (t) 
		free(t);
}
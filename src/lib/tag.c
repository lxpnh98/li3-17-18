#include <string.h>
#include <stdlib.h>
#include "tag.h"
#include "common.h"

struct tag {
    long id;
    char *name;
};

TAG create_tag(long id, char *tagName) {
    TAG t = malloc(sizeof(struct tag));
    t->id = id;
    t->name = mystrdup(tagName);
    return t;
}

long get_tag_id(TAG t) {
    return t->id;
}

char *get_tagName(TAG t) {
    if (t)
        return t->name;
    return NULL;
}

void free_tag(TAG t) {
    if (t)
        free(t);
}

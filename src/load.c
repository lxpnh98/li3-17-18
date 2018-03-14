#include <libxml/parser.h>
#include <libxml/hash.h>
#include "interface.h"
#include "user.h"

struct TCD_community {
    xmlHashTable *users;
    xmlHashTable *posts;
};


TAD_community load(TAD_community com, char* dump_path) //diretoria onde estarão os ficheiros do dump
{
    xmlDoc *doc = NULL;
}

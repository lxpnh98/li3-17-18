#include <stdlib.h> // atoi
#include <libxml/parser.h>
#include <libxml/hash.h>
#include "interface.h"
#include "common.h"
#include "user.h"

struct TCD_community {
    xmlHashTable *users;
    xmlHashTable *posts;
};

void add_user(TAD_community com, USER user) {
}

void processar_users(TAD_community com, xmlDoc *doc)
{
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {

        if (node->properties == NULL) continue;
        char *id_str = (char *)xmlGetProp(node, (const xmlChar *)"id");
        if (id_str == NULL) {
            id_str = (char *)xmlGetProp(node, (const xmlChar *)"Id"); // TODO: fazer isto de maneira dinâmica
        }

        printf("%s\n", id_str);

        long id = atol(id_str);
        USER user = create_user(id, "", NULL);

        printf("%ld\n", get_id(user));
        add_user(com, user);
    }
}

void processar_posts(TAD_community com, xmlDoc *doc)
{
}

TAD_community load(TAD_community com, char* dump_path) //diretoria onde estarão os ficheiros do dump
{
    xmlDoc *doc = NULL;
    char *full_path;

    full_path = make_path(dump_path, USERS);
    if ((doc = xmlReadFile(full_path, NULL, 0)) == NULL) {
        fprintf(stderr, "erro: não conseguiu abrir ficheiro %s\n", full_path);
        exit(-1);
    }
    processar_users(com, doc);
    xmlFreeDoc(doc);

    full_path = make_path(dump_path, POSTS);
    if ((doc = xmlReadFile(full_path, NULL, 0)) == NULL) {
        fprintf(stderr, "erro: não conseguiu abrir ficheiro %s\n", full_path);
        exit(-1);
    }
    processar_posts(com, doc);
    xmlFreeDoc(doc);

    xmlCleanupParser();

    return com;
}

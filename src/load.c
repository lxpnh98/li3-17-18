#include <stdlib.h> // atoi
#include <libxml/parser.h>
#include "interface.h"
#include "common.h"
#include "user.h"
#include "community.h"
#include "post.h"

TAD_community init() {
    return init_community();
}

void processar_users(TAD_community com, xmlDoc *doc)
{
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {

        if (node->properties == NULL) continue;
        long id            = atol((char *)xmlGetProp(node, (const xmlChar *)"Id"));
        if (id < 0) continue;
        long reputation    = atol((char *)xmlGetProp(node, (const xmlChar *)"Reputation"));
        char *display_name =      (char *)xmlGetProp(node, (const xmlChar *)"DisplayName");
        char *short_bio    =      (char *)xmlGetProp(node, (const xmlChar *)"AboutMe");

        USER user = create_user(id, display_name, reputation, short_bio, NULL);

        //printf("%ld %s\n", get_id(user), display_name);
        add_user(com, user);
    }
}

void processar_posts(TAD_community com, xmlDoc *doc)
{
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {
    	long AcceptedAnswer = -1;
        if (node->properties == NULL) continue;
        long id                 = atol((char *)xmlGetProp(node, (const xmlChar *)"Id"));
        if (id < 0) continue;
        enum post_type type     = atoi((char *)xmlGetProp(node, (const xmlChar *)"PostTypeId"));
        if(type == QUESTION && xmlHasProp(node, (const xmlChar *)"AcceptedAnswer")) {
        	AcceptedAnswer = atol((char *)xmlGetProp(node, (const xmlChar *)"AcceptedAnswerId"));
        }

        POST post = create_post(id,type,AcceptedAnswer);
        add_post(com, post);
    }
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

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

TAD_community load(TAD_community com, char* dump_path) //diretoria onde estarão os ficheiros do dump
{
    xmlDoc *doc = NULL;
    xmlNode *node = NULL;
    xmlAttr *attr = NULL;

    char *users_xml_path = make_path(dump_path, USERS);

    if ((doc = xmlReadFile(users_xml_path, NULL, 0)) == NULL) {
        fprintf(stderr, "erro: não conseguiu abrir %s\n", users_xml_path);
        return -1;
    }

    node = xmlDocGetRootElement(doc);

    // Processar Users.xml

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


    // Limpeza
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;

}

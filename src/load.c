#include <stdlib.h>             // atoi
#include <libxml/parser.h>
#include <string.h>
#include "interface.h"
#include "date.h"
#include "common.h"
#include "user.h"
#include "community.h"
#include "tag.h"
#include "post.h"
#include "linked_list.h"

TAD_community init() {
    return init_community();
}

void processar_users(TAD_community com, xmlDoc * doc) {
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {
        if (node->properties == NULL)
            continue;
        long id = atol((char *)xmlGetProp(node, (const xmlChar *)"Id"));
        if (id < 0)
            continue;
        long reputation = atol((char *)xmlGetProp(node, (const xmlChar *)"Reputation"));
        char *display_name = (char *)xmlGetProp(node, (const xmlChar *)"DisplayName");
        char *short_bio = (char *)xmlGetProp(node, (const xmlChar *)"AboutMe");

        USER user = create_user(id, display_name, reputation, short_bio, NULL);

        //printf("%ld %s\n", get_id(user), display_name);
        add_user(com, user);
    }
}

void processar_tags(TAD_community com, xmlDoc * doc) {
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {

        if (node->properties == NULL)
            continue;
        long tag_id = atol((char *)xmlGetProp(node, (const xmlChar *)"Id"));
        char *tagName = (char *)xmlGetProp(node, (const xmlChar *)"TagName");

        TAG tag = create_tag(tag_id, tagName);

        add_tag(com, tag);
    }
}

LONG_list processa_tags(TAD_community com, char *tags_str);

void processar_posts(TAD_community com, xmlDoc * doc) {
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {
        long AcceptedAnswer = -1;
        long userId = -1;
        long parentId = -1;
        int answer_count = 0;
        char *userDisplayName = NULL;
        char *title = NULL;
        char *tags_str = NULL;
        LONG_list tags = NULL;
        long score = 0;

        if (node->properties == NULL)
            continue;
        long id = atol((char *)xmlGetProp(node, (const xmlChar *)"Id"));
        if (id < 0)
            continue;
        enum post_type type = atoi((char *)xmlGetProp(node, (const xmlChar *)"PostTypeId"));
        if (type == QUESTION && xmlHasProp(node, (const xmlChar *)"AcceptedAnswer")) {
            AcceptedAnswer = atol((char *)xmlGetProp(node, (const xmlChar *)"AcceptedAnswerId"));
        }
        if (xmlGetProp(node, (const xmlChar *)"OwnerUserId")) { // TODO: condição redundante nos ficheiros backup dos professores (fazer download)
            userId = atol((char *)xmlGetProp(node, (const xmlChar *)"OwnerUserId"));
        } else {
            userDisplayName = ((char *)xmlGetProp(node, (const xmlChar *)"OwnerDisplayName"));
        }
        if (type == QUESTION) {
            title = ((char *)xmlGetProp(node, (const xmlChar *)"Title"));
            answer_count = atol((char *)xmlGetProp(node, (const xmlChar *)"AnswerCount"));
            tags_str = ((char *)xmlGetProp(node, (const xmlChar *)"Tags"));
            tags = processa_tags(com, tags_str);
        } else if (type == ANSWER) {
            parentId = atol((char *)xmlGetProp(node, (const xmlChar *)"ParentId"));
        } else {
            // TODO: processar outros tipos de posts (3,4,5,6,7)
            continue;
        }

        score = atol((char *)xmlGetProp(node, (const xmlChar *)"Score"));
        char *CreationDate = ((char *)xmlGetProp(node, (const xmlChar *)"CreationDate"));

        POST post = create_post(id, type, AcceptedAnswer, userId, userDisplayName,
                                title, parentId, answer_count, score, CreationDate, tags);
        add_post(com, post);
    }
}

LONG_list processa_tags(TAD_community com, char *tags_str) {
    int n = 0;
    int i = 0;
    int j, k;
    LINKED_LIST l = init_linked_list();
    char tag[1024];
    for (j = 0; tags_str[j] != '\0'; j++) {
        if (tags_str[j] == '<') {
            for (k = 0; tags_str[j + 1] != '>'; k++, j++) {
                tag[k] = tags_str[j + 1];
            }
            tag[k /*+ 1 */ ] = '\0';
            l = add(l, tag);
            n++;
        }
    }
    LONG_list r = create_list(n);
    while (next(l)) {
        set_list(r, i, get_tag_id(get_tag_from_name(com, get_data(l))));
        i++;
        l = next(l);
    }
    return r;
}

TAD_community load(TAD_community com, char *dump_path)  //diretoria onde estarão os ficheiros do dump
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

    full_path = make_path(dump_path, TAGS);
    if ((doc = xmlReadFile(full_path, NULL, 0)) == NULL) {
        fprintf(stderr, "erro: não conseguiu abrir ficheiro %s\n", full_path);
        exit(-1);
    }
    processar_tags(com, doc);
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

TAD_community clean(TAD_community com) {
    return clean_community(com);
}


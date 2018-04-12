/**
@file load.c
Funções que carregam e processam os dados nos ficheiros XML.
*/

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

/**
\brief Macro para obter valor de um atributo de um nodo.
@param node Nodo em questão.
@param str Nome do atributo.
*/
#define GET_PROP(node, str) \
    ((char *)xmlGetProp((node), (const xmlChar *)(str)))

/**
\brief Função que inicializa uma variável do tipo TAD_community.
@returns TAD_community Nova inicialização.
*/
TAD_community init() {
    return init_community();
}

/**
\brief Função que processa os dados do ficheiro Users.xml.
@param com Estrutura onde vai ser guardada a informação.
@param doc Árvore que representa o ficheiro XML.
*/
void processar_users(TAD_community com, xmlDoc * doc) {
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {
        if (node->properties == NULL)
            continue;
        long id = atol(GET_PROP(node, "Id"));
        if (id < 0)
            continue;
        long reputation = atol(GET_PROP(node, "Reputation"));
        char *display_name = GET_PROP(node, "DisplayName");
        char *short_bio = GET_PROP(node, "AboutMe");

        USER user = create_user(id, display_name, reputation, short_bio, NULL);

        add_user(com, user);
    }
}

/**
\brief Função que processa os dados do ficheiro Tags.xml.
@param com Estrutura onde vai ser guardada a informação.
@param doc Árvore que representa o ficheiro XML.
*/
void processar_tags(TAD_community com, xmlDoc * doc) {
    xmlNode *node = xmlDocGetRootElement(doc);
    for (node = node->children; node != NULL; node = node->next) {
        if (node->properties == NULL)
            continue;
        long tag_id = atol(GET_PROP(node, "Id"));
        char *tagName = GET_PROP(node, "TagName");

        TAG tag = create_tag(tag_id, tagName);

        add_tag(com, tag);
    }
}

LONG_list processa_tags(TAD_community com, char *tags_str);

/**
\brief Função que processa os dados do ficheiro Posts.xml.
@param com Estrutura onde vai ser guardada a informação.
@param doc Árvore que representa o ficheiro XML.
*/
void processar_posts(TAD_community com, xmlDoc * doc) {
    xmlNode *node = xmlDocGetRootElement(doc);
    LINKED_LIST answers_to_add = init_linked_list();
    for (node = node->children; node != NULL; node = node->next) {
        long id = -1;
        enum post_type type = 0;
        long AcceptedAnswer = -1;
        long userId = -1;
        long parentId = -1;
        int answer_count = 0;
        char *userDisplayName = NULL;
        char *title = NULL;
        char *tags_str = NULL;
        LONG_list tags = NULL;
        long score = 0;
        long comment_count;

        if (node->properties == NULL)
            continue;
        id = atol(GET_PROP(node, "Id"));
        if (id < 0)
            continue;
        type = atoi(GET_PROP(node, "PostTypeId"));
        if (type == QUESTION && xmlHasProp(node, (const xmlChar *)"AcceptedAnswer")) {
            AcceptedAnswer = atol(GET_PROP(node, "AcceptedAnswerId"));
        }
        if (GET_PROP(node, "OwnerUserId")) {
            userId = atol(GET_PROP(node, "OwnerUserId"));
        } else {
            userDisplayName = GET_PROP(node, "OwnerDisplayName");
        }
        if (type == QUESTION) {
            title = GET_PROP(node, "Title");
            answer_count = atol(GET_PROP(node, "AnswerCount"));
            tags_str = GET_PROP(node, "Tags");
            tags = processa_tags(com, tags_str);
        } else if (type == ANSWER) {
            parentId = atol(GET_PROP(node, "ParentId"));
        } else {
            // TODO: processar outros tipos de posts (3,4,5,6,7)
            continue;
        }

        score = atol(GET_PROP(node, "Score"));
        char *CreationDate = GET_PROP(node, "CreationDate");
        comment_count = atol(GET_PROP(node, "CommentCount"));

        POST post = create_post(id, type, AcceptedAnswer, userId, userDisplayName,
                                title, parentId, answer_count, score, CreationDate,
                                tags, comment_count);
        add_post(com, post, &answers_to_add);
    }

    // adicionar respostas cuja pergunta tem um id maior que o seu
    while(next(answers_to_add)) {
        POST p = get_data(answers_to_add);
        POST parent_post = get_post(com, get_parent_id(p));
        if(parent_post) {
            add_answer(parent_post, get_post_id(p));
        }
        answers_to_add = next(answers_to_add);
    }
}

/**
\brief Função que separa a tag String numa lista de tags.
@param com Estrutura onde está guardada a informação.
@param tags_str String contendo tags de um certo post.
@returns LONG_list Lista dos ids das respetivas tags.
*/
LONG_list processa_tags(TAD_community com, char *tags_str) {
    int i,j;
    int k = 0;
    int n = 0;
    LINKED_LIST l = init_linked_list();
    char tag[1024];
    for (i = 0; tags_str[i] != '\0'; i++) {
        if (tags_str[i] == '<') {
            for (j = 0; tags_str[i + 1] != '>'; j++, i++) {
                tag[j] = tags_str[i + 1];
            }
            tag[j] = '\0';
            l = add(l, tag);
            n++;
        }
    }
    LONG_list r = create_list(n);
    while (next(l)) {
        set_list(r, k, get_tag_id(get_tag_from_name(com, get_data(l))));
        k++;
        l = next(l);
    }
    return r;
}

/**
\brief Função que carrega toda a informação necessária.
@param com Estrutura onde vai ser guardada a informação.
@param dump_path Diretoria onde estão guardados os ficheiros do dump.
@returns TAD_community Estrutura com a informação já armazenada.
*/
TAD_community load(TAD_community com, char *dump_path) {
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

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param com Estrutura onde está guardada a informação.
@returns TAD_community Estrutura passada como argumento.
*/
TAD_community clean(TAD_community com) {
    return clean_community(com);
}

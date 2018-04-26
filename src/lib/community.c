/**
@file community.c
Descrição da estrutura de dados e funções que respondem as queries.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>               // floor, log10
#include <libxml/hash.h>
#include <string.h>
#include <assert.h>
#include "user.h"
#include "pair.h"
#include "list.h"
#include "linked_list.h"
#include "post.h"
#include "tag.h"
#include "date.h"
#include "common.h"
#include "community.h"

/**
/brief Tamanho inicial das HashTables.
*/
enum {
    INIT_USERS = 10,
    INIT_POSTS = 10,
    INIT_TAGS = 10,
};
/** \brief Estrutura que armazena a informação */
struct TCD_community {
    /** \brief Tabela de hash dos utilizadores */
    xmlHashTable *users;
    /** \brief Lista ligada dos utilizadores  */
    LINKED_LIST user_list;
    /** \brief Tabela de hash das tags cujas chaves são os ids */
    xmlHashTable *tags_from_id;
    /** \brief Tabela de hash das tags cujas chaves são os nomes */
    xmlHashTable *tags_from_name;
    /** \brief Tabela de hash dos posts */
    xmlHashTable *posts;
    /** \brief Lista ligada dos posts */
    LINKED_LIST post_list;
};

/**
\brief Função que inicializa uma variável do tipo TAD_community.
@returns TAD_community Nova inicialização.
*/
TAD_community init_community() {
    TAD_community new = malloc(sizeof(struct TCD_community));
    new->users = xmlHashCreate(INIT_USERS);
    new->user_list = init_linked_list();
    new->posts = xmlHashCreate(INIT_POSTS);
    new->post_list = init_linked_list();
    new->tags_from_id = xmlHashCreate(INIT_TAGS);
    new->tags_from_name = xmlHashCreate(INIT_TAGS);
    return new;
}

/**
\brief Função que adiciona um utilizador.
@param com Estrutura onde vai ser guardada a informação.
@param user Utilizador a adicionar.
*/
void add_user(TAD_community com, USER user) {
    char *str_user_id = ltoa(get_id(user));
    xmlHashAddEntry(com->users, (const xmlChar *)str_user_id, user);
    com->user_list = add(com->user_list, user);
    free(str_user_id);
}

/**
\brief Função que adiciona uma tag.
@param com Estrutura onde vai ser guardada a informação.
@param tag Tag a adicionar.
*/
void add_tag(TAD_community com, TAG tag) {
    char *tag_id_str = ltoa(get_tag_id(tag));
    char *tag_name = get_tagName(tag);
    xmlHashAddEntry(com->tags_from_id, (const xmlChar *)tag_id_str, tag);
    xmlHashAddEntry(com->tags_from_name, (const xmlChar *)tag_name, tag);
    free(tag_id_str);
    free(tag_name);
}

void insert_by_date(TAD_community com, LONG_list l, POST p, int n, int max_n);

/**
\brief Função que adiciona um post à estrutura de dados, atualizando a
 * informação do respetivo utilizador e pergunta, se for resposta. Neste último
 * caso, se a pergunta não for encontrada na estrutura de dados, a resposta é
 * adicionada a uma lista para ser adicionada posteriormente.
@param com Estrutura onde vai ser guardada a informação.
@param post Post a adicionar.
@param answers_to_add Posts cujas respetivas questões têm um id maior que o próprio - respostas têm que ser adicionadas no fim
*/
void add_post(TAD_community com, POST post, LINKED_LIST *answers_to_add) {
    LONG_list l;
    int user_id = get_user_id(post);
    if (user_id > 0) {
        USER u = get_user(com, user_id);

        // Adicionar post aos 10 últimos posts
        l = get_posts_long_list(u);
        insert_by_date(com, l, post, MIN2(get_post_count(u), 10), 10);
        set_post_list(u, l);
        free_list(l);

        set_post_count(u, get_post_count(u) + 1);

        // Se for resposta, adicionar à lista de respostas da respetiva pergunta
        if (get_type(post) == ANSWER) {
            POST parent_post = get_post(com, get_parent_id(post));
            if (parent_post) {
                add_answer(parent_post, get_post_id(post));
            } else {
                *answers_to_add = add(*answers_to_add, post);
            }
        }
    }
    char *str_post_id = itoa(get_post_id(post));
    xmlHashAddEntry(com->posts, (const xmlChar *)str_post_id, post);
    com->post_list = add(com->post_list, post);
    free(str_post_id);
}

/**
\brief Função que devolve um utilizador correspondente a um dado id.
@param com Estrutura onde está guardada a informação.
@param id Id do utilizador a returnar.
@returns USER Utilizador procurado.
*/
USER get_user(TAD_community com, long id) {
    char *id_str = ltoa(id);
    USER u = (USER)xmlHashLookup(com->users, (const xmlChar *)id_str);
    free(id_str);
    return u;
}

/**
\brief Função que devolve um post correspondente a um dado id.
@param com Estrutura onde está guardada a informação.
@param id Id do post a returnar.
@returns POST Post procurado.
*/
POST get_post(TAD_community com, long id) {
    char *id_str = ltoa(id);
    POST p = (POST)xmlHashLookup(com->posts, (const xmlChar *)id_str);
    free(id_str);
    return p;
}

/**
\brief Função que devolve uma tag correspondente a um dado id.
@param com Estrutura onde está guardada a informação.
@param id Id da tag a returnar.
@returns TAG Tag procurada.
*/
TAG get_tag_from_id(TAD_community com, long id) {
    char *id_str = ltoa(id);
    TAG t = (TAG)xmlHashLookup(com->tags_from_id, (const xmlChar *)id_str);
    free(id_str);
    return t;
}

/**
\brief Função que devolve uma tag correspondente a uma dada String nome.
@param com Estrutura onde está guardada a informação.
@param id String nome da tag a returnar.
@returns TAG Tag procurada.
*/
TAG get_tag_from_name(TAD_community com, char *name) {
    return (TAG)xmlHashLookup(com->tags_from_name, (const xmlChar *)name);
}

/**
\brief Função que devolve o nome do autor de um dado post.
@param com Estrutura onde está guardada a informação.
@param p Post.
@returns char* String do nome do autor.
*/
char *get_author_name(TAD_community com, POST p) {
    long id = get_user_id(p);
    if (id == -1) {
        return get_user_display_name(p);
    } else {
        USER u = get_user(com, id);
        return get_display_name(u);
    }
}

/**
\brief Função que devolve o título da pergunta de um dado post.
@param com Estrutura onde está guardada a informação.
@param p Post.
@returns char* String do título da pergunta.
*/
char *get_question_title(TAD_community com, POST p) {
    char *title = get_title(p);
    if (title == NULL) {
        long parentId = get_parent_id(p);
        POST p = get_post(com, parentId);
        title = get_title(p);
    }
    return title;
}

/**
\brief Função que responde à interrogação 1: Dado o identificador de um post, a função deve retor-
 * nar o tı́tulo do post e o nome (não o ID) de utilizador do autor. Se o post
 * for uma resposta, a função deverá retornar informações (tı́tulo e utilizador)
 * da pergunta correspondente.
@param com Estrutura onde está guardada a informação.
@param id Id do post.
@returns STR_pair Par de Stings (Título, Nome do autor).
*/
STR_pair info_from_post(TAD_community com, long id) {
    POST p = get_post(com, id);
    if (p == NULL)              // TODO: fazer logging de erros (post == NULL, user == NULL, etc.)
        return NULL;
    char *title = get_question_title(com, p);
    char *author_name = get_author_name(com, p);
    STR_pair pair = create_str_pair(title, author_name);
    free(title);
    free(author_name);
    return pair;
}

void insert_by_post_count(TAD_community com, LONG_list l, USER u, int n, int max_n);

/**
\brief Função que responde à interrogação 2: Pretende obter o top N utilizadores com maior número
 * de posts de sempre. Para isto, devem ser considerados tanto perguntas
 * quanto respostas dadas pelo respectivo utilizador.
@param com Estrutura onde está guardada a informação.
@param N Tamanho da lista a returnar.
@returns LONG_list Lista dos N ids dos utilizadores com maior número de posts.
*/
LONG_list top_most_active(TAD_community com, int N) {
    LONG_list most_active = create_list(N);    //TODO: melhorar nomes das variáveis
    LINKED_LIST l = com->user_list;
    USER u;
    int n = 0;
    while (next(l) != NULL) {
        u = (USER)get_data(l);
        insert_by_post_count(com, most_active, u, MIN2(n, N), N);
        l = next(l);
        n++;
    }
    return most_active;
}

/**
\brief Função que insere o id de um utilizador, por ordem decrescente do número de posts, numa lista.
@param com Estrutura onde está guardada a informação.
@param l Lista onde o id do utilizador será inserido.
@param u Utilizador.
@param n Atual número de elementos na lista.
@param max_n Número máximo de elementos na lista.
*/
void insert_by_post_count(TAD_community com, LONG_list l, USER u, int n, int max_n) {
    int i;
    int post_count = get_post_count(u);
    USER u2;
    for (i = 0; i < n; i++) {
        u2 = get_user(com, get_list(l, i));
        if (get_post_count(u2) < post_count) {
            break;
        }
    }
    if (i < max_n)
        push_insert(l, i, get_id(u));
}

/**
\brief Função que responde à interrogação 3: Dado um intervalo de tempo arbitrário,
 * obter o número total de posts (identificando perguntas e respostas separadamente) neste perı́odo.
@param com Estrutura onde está guardada a informação.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns LONG_pair Par de longs (Perguntas, Respostas).
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end) {
    long questions = 0;
    long answers = 0;
    LONG_pair l = create_long_pair(questions, answers);
    LINKED_LIST x = com->post_list;
    POST p;

    while (next(x)) {
        p = (POST)get_data(x);
        Date d = get_date(p);
        if (is_between(d, begin, end)) {
            if (get_type(p) == QUESTION) {
                questions++;
            } else {
                answers++;
            }
        }
        x = next(x);
        free_date(d);
    }

    set_fst_long(l, questions);
    set_snd_long(l, answers);
    return l;
}

/**
\brief Função que responde à Interrogação 4: Dado um intervalo de tempo arbitrário, retornar todas
 * as perguntas contendo uma determinada tag. O retorno da função deverá ser
 * uma lista com os IDs das perguntas ordenadas em cronologia inversa.
@param com Estrutura onde está guardada a informação.
@param tag_name Nome da tag.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns LONG_list Lista dos ids das perguntas com a tag.
*/
LONG_list questions_with_tag(TAD_community com, char *tag_name, Date begin, Date end) {
    LINKED_LIST l = init_linked_list();
    LINKED_LIST x = com->post_list;
    POST p;
    int post_count = 0;
    TAG tag = get_tag_from_name(com, tag_name);
    if (tag == NULL)
        return NULL;
    long tag_id = get_tag_id(tag);

    while (next(x)) {
        p = (POST)get_data(x);
        Date post_date = get_date(p);
        if (is_between(post_date, begin, end)) {
            if (get_type(p) == QUESTION && has_tag(p, tag_id)) {
                l = add(l, p);
                post_count++;
            }
        }
        free_date(post_date);
        x = next(x);
    }

    LONG_list r = create_list(post_count);
    int n = 0;
    LINKED_LIST tmp = l;
    while (next(tmp) != NULL) {
        p = (POST)get_data(tmp);
        insert_by_date(com, r, p, MIN2(n, post_count), post_count);
        tmp = next(tmp);
        n++;
    }
    free_linked_list(l, NULL);
    return r;
}

/**
\brief Função que insere o id de um post, por ordem conológica inversa, numa lista.
@param com Estrutura onde está guardada a informação.
@param l Lista onde o id do post será inserido.
@param p Post.
@param n Atual número de elementos na lista.
@param max_n Número máximo de elementos na lista.
*/
void insert_by_date(TAD_community com, LONG_list l, POST p, int n, int max_n) {
    int i;
    Date post_date = get_date(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = get_post(com, get_list(l, i));
        Date p2_date = get_date(p2);
        if (isBefore(p2_date, post_date)) {
            break;
        }
        free_date(p2_date);
    }
    free_date(post_date);
    if (i < max_n)
        push_insert(l, i, get_post_id(p));
}

/**
\brief Função que responde à Interrogação 5: Dado um ID de utilizador, devolver a informação do
 * seu perfil (short bio) e os IDs dos seus 10 últimos posts (perguntas ou res-
 * postas), ordenados por cronologia inversa.
@param com Estrutura onde está guardada a informação.
@param id Id do utilizador.
@returns USER Estrutura com a bio e uma lista dos últimos 10 posts do utulizador.
*/
USER get_user_info(TAD_community com, long id) {
    USER user;
    char *bio;
    LONG_list l;

    USER u = get_user(com, id);
    if (u == NULL)
        return NULL;

    bio = get_bio(u);
    l = get_posts_long_list(u);

    user = create_user(id, "", 0, bio, NULL);
    set_post_list(user, l);

    free(bio);
    free_list(l);
    return user;
}

void insert_by_score(TAD_community com, LONG_list l, POST p, int n, int max_n);

/**
\brief Função que responde à Interrogação 6: Dado um intervalo de tempo arbitrário, devolver os IDs
 * das N respostas com mais votos, em ordem decrescente do número de votos.
@param com Estrutura onde está guardada a informação.
@param N Número pretendido de respostas.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns LONG_list Lista com os ids das N respostas com mais votos.
*/
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end) {
    LONG_list list = create_list(N);
    LINKED_LIST l = com->post_list;
    POST p;
    int n = 0;
    while (next(l) != NULL) {
        p = (POST)get_data(l);
        insert_by_score(com, list, p, MIN2(n, N), N);
        l = next(l);
        n++;
    }
    return list;
}

/**
\brief Função que insere o id de um post, por ordem decrescente de pontuação, numa lista.
@param com Estrutura onde está guardada a informação.
@param l Lista onde o id do post será inserido.
@param p Post.
@param n Atual número de elementos na lista.
@param max_n Número máximo de elementos na lista.
*/
void insert_by_score(TAD_community com, LONG_list l, POST p, int n, int max_n) {
    int i;
    int post_score = get_score(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = get_post(com, get_list(l, i));
        if (post_score > get_score(p2)) {
            break;
        }
    }
    if (i < max_n)
        push_insert(l, i, get_post_id(p));
}

void insert_by_answer_count(TAD_community com, LONG_list l, POST p, int n, int max_n);

/**
\brief Função que responde à Interrogação 7: Dado um intervalo de tempo arbitrário, devolver as
 * IDs das N perguntas com mais respostas, em ordem decrescente do número
 * de votos.
@param com Estrutura onde está guardada a informação.
@param N Número pretendido de respostas.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns LONG_list Lista com os ids das N respostas com mais respostas.
*/
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
    LONG_list list = create_list(N);
    LINKED_LIST l = com->post_list;
    POST p;
    int n = 0;
    while (next(l) != NULL) {
        p = (POST)get_data(l);
        Date d = get_date(p);
        if (get_type(p) == QUESTION && (is_between(d, begin, end))) {
            insert_by_answer_count(com, list, p, MIN2(n, N), N);
            n++;
        }
        l = next(l);
        free_date(d);
    }
    return list;
}

/**
\brief Função que insere o id de um post, por ordem decrescente do núemro de respostas, numa lista.
@param com Estrutura onde está guardada a informação.
@param l Lista onde o id do post será inserido.
@param p Post.
@param n Atual número de elementos na lista.
@param max_n Número máximo de elementos na lista.
*/
void insert_by_answer_count(TAD_community com, LONG_list l, POST p, int n, int max_n) {
    int i;
    int post_count = get_answer_count(p);
    POST p2;
    for (i = 0; i < n; i++) {
        p2 = get_post(com, get_list(l, i));
        if (get_answer_count(p2) > post_count) {
            break;
        }
    }
    if (i < max_n) {
        push_insert(l, i, get_post_id(p));
    }
}

LINKED_LIST separate_title(char *title);

int find_word(LINKED_LIST title, char *word);

/**
\brief Função que responde à Interrogação 8: Dado uma palavra, devolver uma lista com os IDs de N
 * perguntas cujos títulos a contenham, ordenados por cronologia inversa.
@param com Estrutura onde está guardada a informação.
@param word Palavra a procurar.
@param N Número pretendido de respostas.
@returns LONG_list Lista com os ids das N perguntas cujo título contem a palavra.
*/
LONG_list contains_word(TAD_community com, char *word, int N) {
    LINKED_LIST titulo;
    LINKED_LIST x = com->post_list;
    LONG_list r = create_list(N);
    int i;
    for (i = 0; i < N; i++)
        set_list(r, i, -1);
    POST p;
    int n = 0;
    while (next(x) != NULL) {
        p = (POST)get_data(x);
        if (get_type(p) == QUESTION) {
            char *title = get_title(p);
            titulo = separate_title(title);
            free(title);
            if (find_word(titulo, word)) {
                insert_by_date(com, r, p, MIN2(n, N), N);
                n++;
            }
            free_linked_list(titulo, free);
        }
        x = next(x);
    }
    return r;
}

/**
\brief Função que separa a String do título numa lista ligada.
@param title Título de uma pergunta.
@returns LINKED_LIST Lista ligada com os caracteres do título passado como argumento.
*/
LINKED_LIST separate_title(char *title) {
    int i = 0;
    int r = 0;
    int tam = strlen(title);
    char word[1024];
    LINKED_LIST titulo = init_linked_list();
    while (i <= tam) {
        if (title[i] == ' ' || title[i] == '.' || title[i] == ',' ||
            title[i] == '!' || title[i] == '?' || title[i] == ';' || title[i] == ';' || title[i] == ':' || title[i] == '\0') {
            word[r] = '\0';
            titulo = add(titulo, mystrdup(word));
            i++;
            r = 0;
        } else {
            word[r] = title[i];
            r++;
            i++;
        }
    }
    return titulo;
}

/**
\brief Função que separa a String do título numa lista ligada.
@param LINKED_LIST Lista ligada com o título de uma pergunta.
@param word Palavra a procurar.
@returns int Inteiro com valor boleano.
*/
int find_word(LINKED_LIST title, char *word) {
    char *titulo;
    while (next(title)) {
        titulo = get_data(title);
        if (strcmp(titulo, word) == 0) {
            return 1;
        } else {
            title = next(title);
        }
    }
    return 0;
}

int both_users_participate(TAD_community com, POST p, long id1, long id2);

/**
\brief Função que responde à Interrogação 9: Dados os IDs de dois utilizadores, devolver as últimas
 * N perguntas (cronologia inversa) em que participaram dois utilizadores es-
 * pecı́ficos. Note que os utilizadores podem ter participado via pergunta ou
 * respostas.
@param com Estrutura onde está guardada a informação.
@param id1 Id de um utilizador.
@param id2 Id de um utilizador.
@param N Número pretendido de perguntas.
@returns LONG_list Lista com os ids das N perguntas em que os dois utilizadores participaram.
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N) {
    LINKED_LIST x = com->post_list;
    POST p;
    LONG_list r = create_list(N);
    int i;
    for (i = 0; i < N; i++)
        set_list(r, i, -1);
    int n = 0;
    while (next(x)) {
        p = (POST)get_data(x);
        if (get_type(p) == QUESTION && both_users_participate(com, p, id1, id2)) {
            insert_by_date(com, r, p, MIN2(n, N), N);
            n++;
        }
        x = next(x);
    }
    return r;
}

/**
\brief Função que verifica se dois dados utilizadores participam num dado post.
@param com Estrutura onde está guardada a informação.
@param p Post.
@param id1 Id de um utilizador.
@param id2 Id de um utilizador.
@returns int Inteiro com valor boleano.
*/
int both_users_participate(TAD_community com, POST p, long id1, long id2) {
    assert(get_type(p) == QUESTION);
    int i, answer_count;
    POST p2;
    int match_id1 = 0, match_id2 = 0;
    long question_user_id = get_user_id(p);
    if (question_user_id == id1)
        match_id1 = 1;
    if (question_user_id == id2)
        match_id2 = 1;
    LONG_list answer_ids = get_answers(p);
    answer_count = get_answer_count(p);
    for (i = 0; i < answer_count; i++) {
        long post_id = get_list(answer_ids, i);
        if (post_id < 0)        // Nem todas as questões estão a ser introduzidas na lista, assim os ids não são de nenhum utilizador.
            continue;
        p2 = get_post(com, post_id);
        if (p2 != NULL) {
            int user_id = get_user_id(p2);
            if (user_id == id1)
                match_id1 = 1;
            if (user_id == id2)
                match_id2 = 1;
        }
    }
    return match_id1 && match_id2;
}

long get_reputation(TAD_community com, long id);

/**
\brief Função que responde à Interrogação 10: Dado o ID de uma pergunta, obter a melhor resposta. Para isso
 * deverá usar a função de média ponderada abaixo:
 * (Scr*0.45) + (Rep*0.25) + (Vot*0.2) + (Comt*0.1).
@param com Estrutura onde está guardada a informação.
@param id Id da pergunta.
@returns long Id da melhor resposta à pergunta.
*/
long better_answer(TAD_community com, long id) {
    POST p, a;
    int i, answer_count;
    long media, scr, rep, vot, comt;
    long best_media = 0;
    long best_answer = -1;
    p = get_post(com, id);
    answer_count = get_answer_count(p);
    LONG_list x = get_answers(p);
    for (i = 0; i < answer_count && (get_list(x, i) != -1); i++) {
        a = get_post(com, get_list(x, i));
        scr = get_score(a);
        rep = get_reputation(com, get_user_id(a));
        vot = scr;
        comt = get_comment_count(a);
        media = ((scr * 0.45) + (rep * 0.25) + (vot * 0.2) + (comt * 0.1));

        if (media > best_media) {
            best_media = media;
            best_answer = get_post_id(a);
        }
    }
    return best_answer;
}

/**
\brief Função que retorna a reputação de um dado utilizador.
@param com Estrutura onde está guardada a informação.
@param id Id do Utilizador.
@returns long Reputação do utilizador.
*/
long get_reputation(TAD_community com, long id) {
    USER u;
    long rep = 0;
    u = get_user(com, id);
    rep = get_rep(u);
    return rep;
}

LONG_list best_rep_users(TAD_community com, int N);

void insert_by_rep(TAD_community com, LONG_list l, USER u, int n, int max_n);

LONG_list most_used_tags(TAD_community com, int N, LONG_list best_rep, Date begin, Date end);

int posted_by_users(POST p, int N, LONG_list best_rep);

/** \brief Estrutura que armazena a informação de uma tag e as vezes que esta foi usada */
typedef struct tag_count {
    /** \brief Id da tag */
    long id;
    /** \brief String do Nome da tag */
    char *name;
    /** \brief Número de vezes que a tag foi usada */
    int count;
} *TAG_COUNT;

void insert_by_tag_count(xmlHashTable *tag_count_hash, LONG_list l, TAG_COUNT t, int n, int max_n);

/**
\brief Função que responde à Interrogação 11: Dado um intervalo arbitrário de tempo, devolver os
 * identificadores das N tags mais usadas pelos N utilizadores com melhor reputação.
 * Em ordem decrescente do número de vezes em que a tag foi usada.
@param com Estrutura onde está guardada a informação.
@param N Número pretendido de perguntas.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns LONG_list Lista com os ids das N tags mais usadas pelos N utilizadores com melhor reputação.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end) {
    LONG_list best_rep = best_rep_users(com, N);
    LONG_list most_used = most_used_tags(com, N, best_rep, begin, end);
    free_list(best_rep);
    return most_used;
}

/**
\brief Função que retorna uma lista dos N utilizadores com melhor reputação.
@param com Estrutura onde está guardada a informação.
@param N Número pretendido de utilizadores.
@returns LONG_list Lista com os ids dos N utilizadores com melhor reputação.
*/
LONG_list best_rep_users(TAD_community com, int N) {
    LONG_list result = create_list(N);
    LINKED_LIST l = com->user_list;
    int n = 0;
    while (next(l)) {
        USER u = get_data(l);
        insert_by_rep(com, result, u, MIN2(n, N), N);
        n++;
        l = next(l);
    }
    return result;
}

/**
\brief Função que insere um utilizador numa lista por ordem decrescente de reputação.
@param com Estrutura onde está guardada a informação.
@param l Lista onde o id do post será inserido.
@param u Utilizador.
@param n Atual número de elementos na lista.
@param max_n Número máximo de elementos na lista.
*/
void insert_by_rep(TAD_community com, LONG_list l, USER u, int n, int max_n) {
    int i;
    int rep = get_rep(u);
    USER u2;
    for (i = 0; i < n; i++) {
        u2 = get_user(com, get_list(l, i));
        if (get_rep(u2) > rep) {
            break;
        }
    }
    if (i < max_n) {
        push_insert(l, i, get_id(u));
    }
}

/**
\brief Função que retorna uma lista das N tags mais usadas pelos utilizadores com melhor reputação.
@param com Estrutura onde está guardada a informação.
@param N Número pretendido de tags.
@param best_rep Lista dos ids dos N utilizadores com melhor reputação.
@param begin Data de início da contagem.
@param end Data do fim da contagem.
@returns LONG_list Lista com os ids dos N utilizadores com melhor reputação.
*/ 
LONG_list most_used_tags(TAD_community com, int N, LONG_list best_rep, Date begin, Date end) {
    LINKED_LIST l = com->post_list;
    xmlHashTable *tag_count_hash = xmlHashCreate(INIT_TAGS);
    LINKED_LIST tag_count_list = init_linked_list();
    int i;

    // Contar tags
    while (next(l)) {
        POST p = get_data(l);
        Date creation_date = get_date(p);
        if (is_between(creation_date, begin, end) && posted_by_users(p, N, best_rep)) {
            int ntags = get_ntags(p);
            LONG_list tags = get_tags(p);
            TAG_COUNT t;
            for (i = 0; i < ntags; i++) {
                char *id_str = ltoa(get_list(tags, i));
                t = (TAG_COUNT)xmlHashLookup(tag_count_hash, (const xmlChar *)id_str);
                if (t == NULL) {
                    t = malloc(sizeof(struct tag_count));
                    t->id = get_list(tags, i);
                    t->name = mystrdup(get_tagName(get_tag_from_id(com, get_list(tags, i))));
                    t->count = 0;
                    xmlHashAddEntry(tag_count_hash, (const xmlChar *)id_str, t);
                    tag_count_list = add(tag_count_list, t);
                }
                free(id_str);
                t->count++;
            }
        }
        l = next(l);
        free_date(creation_date);
    }

    // Inserir por ordem
    int n = 0;
    LONG_list r = create_list(N);
    for (i = 0; i < N; i++)
        set_list(r, i, -1);
    LINKED_LIST x = tag_count_list;
    while (next(x)) {
        TAG_COUNT t = get_data(x);
        insert_by_tag_count(tag_count_hash, r, t, MIN2(n, N), N);
        n++;
        x = next(x);
    }
    free_linked_list(tag_count_list, NULL);
    xmlHashFree(tag_count_hash, NULL);

    return r;
}

/**
\brief Função que verifica se um dado post foi publicado por algum dos N utilizadores com melhor reputação.
@param p Post.
@param N Número de elementos da lista.
@param best_rep Lista dos ids dos N utilizadores com melhor reputação.
@returns int Inteiro com valor boleano.
*/
int posted_by_users(POST p, int N, LONG_list best_rep) {
    long user_id = get_user_id(p);
    int i;
    for (i = 0; i < N; i++) {
        if (user_id == get_list(best_rep, i)) {
            return 1;
        }
    }
    return 0;
}

/**
\brief Função que insere uma tag numa lista por ordem decrescente de utilização.
@param tag_count_hash Tabela de hash com os ids das tags.
@param l Lista onde o id da tag será inserido.
@param t Estrutura de uma tag com contagem.
@param n Atual número de elementos na lista.
@param max_n Número máximo de elementos na lista.
*/
void insert_by_tag_count(xmlHashTable *tag_count_hash, LONG_list l, TAG_COUNT t, int n, int max_n) {
    int i;
    int count = t->count;
    TAG_COUNT t2;
    for (i = 0; i < n; i++) {
        char *id_str = ltoa(get_list(l, i));
        t2 = xmlHashLookup(tag_count_hash, (const xmlChar *)id_str);
        free(id_str);
        if (t2->count > count) {
            break;
        }
    }
    if (i < max_n) {
        push_insert(l, i, t->id);
    }
}

/**
\brief Função que liberta a memória ocupada pela estrutura de dados.
@param com Estrutura onde está guardada a informação.
@returns TAD_community Estrutura passada como argumento.
*/
TAD_community clean_community(TAD_community com) {
    free_linked_list(com->user_list, free_userv);
    free_linked_list(com->post_list, free_postv);
    xmlHashFree(com->users, NULL);
    xmlHashFree(com->tags_from_id, NULL);
    xmlHashFree(com->tags_from_name, NULL);
    xmlHashFree(com->posts, NULL);
    free(com);
    return com;
}
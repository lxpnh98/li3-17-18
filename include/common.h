#ifndef __MY_COMMON__
#define __MY_COMMON__
char * mystrdup (const char *s);

enum dump_type {
    BADGES,
    COMMENTS,
    POST_HISTORY,
    POST_LINKS,
    POSTS,
    TAGS,
    USERS,
    VOTES,
};

char *make_path(const char *, enum dump_type);

#endif

#include "user.h"
#include "post.h"

typedef struct TCD_community *TAD_community;

TAD_community init_community();

void add_user(TAD_community com, USER user);

void add_post(TAD_community com, POST post);

#include "user.h"
#include "tag.h"

typedef struct TCD_community *TAD_community;

TAD_community init_community();

void add_user(TAD_community com, USER user);

void add_tag(TAD_community com, TAG tag);

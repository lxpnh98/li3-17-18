#ifndef __TAG__
#define __TAG__
typedef struct tag *TAG;

TAG create_tag(long id, char *tagName);

long get_tag_id(TAG t);

char *get_tagName(TAG t);

void free_tag(TAG t);
#endif

#ifndef __TAG__
#define __TAG__
typedef struct tag* TAG;

TAG create_tag(char *tagName);
char* get_tagName(TAG t);

void free_tag(TAG t);
#endif
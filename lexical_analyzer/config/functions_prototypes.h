#ifndef FUNCTIONS_PROTOTYPES_HEADER_FILE
#define FUNCTIONS_PROTOTYPES_HEADER_FILE

#include "types.h"

void add_word(WL *head_ptr, char *new_word);
WL extract_words(char* fileName);
void display_words_list(WL head, char *msg);

#endif
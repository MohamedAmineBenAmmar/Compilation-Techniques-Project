#ifndef FUNCTIONS_PROTOTYPES_HEADER_FILE
#define FUNCTIONS_PROTOTYPES_HEADER_FILE

#include "types.h"

// BaseNode functions
void display(BaseNode* head);
void append(BaseNode **head, char *nonTerminal, SLL sll);
BaseNode *find(BaseNode *head, char *nonTerminal);
int sll_length(SLL head);

// SLL functions
SLL sll_constructor();
void sll_append(SLL *head, char *string, int allow_duplicate_values);
SLL sll_find(SLL head, char *string);
void concat(SLL *dest, SLL src, int epsilon_flag, int allow_duplicate_values);
void display_sll(SLL head);

// Helper functions
int isNonTerminal(Grammar g, char *string);

// Stack functions
StringStack push(StringStack head, char *string);
StringStack pop(StringStack head);
char *peek(StringStack head);
int empty(StringStack head);
void print_stack(StringStack head);

StringStack bulk_push(StringStack head, char *word);

#endif
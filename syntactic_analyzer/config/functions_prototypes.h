#ifndef FUNCTIONS_PROTOTYPES_HEADER_FILE
#define FUNCTIONS_PROTOTYPES_HEADER_FILE

#include "types.h"

// BaseNode functions
void display(BaseNode* head);
void append(BaseNode **head, char *nonTerminal, SLL sll);
BaseNode *find(BaseNode *head, char *nonTerminal);

// SLL functions
SLL sll_constructor();
void sll_append(SLL *head, char *string);
SLL sll_find(SLL head, char *string);
void concat(SLL *dest, SLL src, int epsilon_flag);

// Helper functions
int isNonTerminal(Grammar g, char *string);

#endif
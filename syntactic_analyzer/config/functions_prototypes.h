#ifndef FUNCTIONS_PROTOTYPES_HEADER_FILE
#define FUNCTIONS_PROTOTYPES_HEADER_FILE

#include "types.h"

// BaseNode functions
void display(BaseNode* head);
void append(BaseNode **head, char *nonTerminal, SLL sll);

// SLL functions
SLL sll_constructor();
void sll_append(SLL *head, char *string);

// Helper functions
int isNonTerminal(Grammar g, char* string);

BaseNode *find(BaseNode *head, char *nonTerminal);

#endif
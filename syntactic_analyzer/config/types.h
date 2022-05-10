#ifndef TYPES_HEADER_FILE
#define TYPES_HEADER_FILE

// Types definition

// Type definition of a string linked list
typedef struct StringLinkedListNode
{
    char *string;
    struct StringLinkedListNode *next;
} StringLinkedListNode;

typedef StringLinkedListNode *SLL;
typedef StringLinkedListNode *StringStack;

// Type definition of BaseNode, this type presents an abstraction of an Grammar, Follow, First types
typedef struct BaseNode
{
    char *nonTerminal;
    SLL sll;
    struct BaseNode *next;
} BaseNode;

typedef BaseNode *Grammar;
typedef BaseNode *First;
typedef BaseNode *Follow;
// typedef BaseNode *LL1PT;

typedef struct LL1PTRow
{
    char *nonTerminal;
    SLL keys;
    SLL values;
    struct LL1PTRow *next;
} LL1PTRow;

typedef LL1PTRow *LL1PT;



#endif
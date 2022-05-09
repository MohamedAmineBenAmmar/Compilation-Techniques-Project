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

// Define the structure for the LL1 parsing table
typedef struct LL1PTCols
{
    SLL terminals;
    SLL production_rules;    
} LL1PTCols;

typedef struct LL1PTRow
{
    char *nonTerminal;
    LL1PTCols cols;
    struct LL1PTRow *next;
} LL1PTRow;

typedef LL1PTRow *LL1PT;

#endif
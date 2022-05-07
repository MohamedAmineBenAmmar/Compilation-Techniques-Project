#ifndef TYPES_HEADER_FILE
#define TYPES_HEADER_FILE

#include <stdlib.h>
#include <stdio.h>

// Types definition
typedef struct WLNode
{
    char word[5];
    struct WLNode *next;
} WLNode;

typedef WLNode *WL;

#endif
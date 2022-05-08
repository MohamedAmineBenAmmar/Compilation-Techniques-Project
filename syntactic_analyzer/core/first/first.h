#ifndef FIRST_HEADER_FILE
#define FIRST_HEADER_FILE

#include "../../config/types.h"

First first_calculation(Grammar g);
void firstOf(Grammar main_node, Grammar secondary_node, Grammar g, SLL *firstOfArg, int *replace);

#endif
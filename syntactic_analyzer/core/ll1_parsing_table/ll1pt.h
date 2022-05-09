#ifndef LL1PT_HEADER_FILE
#define LL1PT_HEADER_FILE

#include "../../config/types.h"

LL1PT ll1pt_constructor(Grammar grammar, First first, Follow follow);
void display_ll1pt(LL1PT ll1pt, Grammar grammar);

#endif
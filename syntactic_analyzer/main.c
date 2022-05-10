#include <stdio.h>
#include "converter/converter.h"
#include "config/functions_prototypes.h"
#include "core/first/first.h"
#include "core/follow/follow.h"
#include "core/ll1_parsing_table/ll1pt.h"

#include <string.h>


int main(int argc, char **argv)
{
    // Extracting the grammar from the tmp folder
    Grammar grammar;
    First first;
    Follow follow;
    LL1PT ll1pt;

    // Display the Grammar
    grammar = convert(argv[1]);
    printf("Grammar:\n");
    display(grammar);
    printf("\n");

    // Display the First
    first = first_calculation(grammar);
    printf("First:\n");
    display(first);
    printf("\n");

    // Display the follow
    follow = follow_calculation(grammar, first);
    printf("Follow:\n");
    display(follow);
    printf("\n");

    // Display LL1 table skeleton
    ll1pt = ll1pt_constructor(grammar, first, follow);
    printf("LL1 Parsing Table:\n");
    display_ll1pt(ll1pt, grammar);

  
    return 0;
}
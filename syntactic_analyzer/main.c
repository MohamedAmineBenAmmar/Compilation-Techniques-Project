#include <stdio.h>
#include "converter/converter.h"
#include "config/functions_prototypes.h"
#include "core/first/first.h"

int main(int argc, char **argv)
{
    // Extracting the grammar from the tmp folder
    Grammar grammar;
    First first;
    Follow follow;

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

    return 0;
}
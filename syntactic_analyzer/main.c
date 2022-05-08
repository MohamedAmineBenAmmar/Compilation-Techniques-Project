#include <stdio.h>
#include "converter/converter.h"
#include "config/functions_prototypes.h"
#include "core/first/first.h"

int main(int argc, char **argv)
{
    // Extracting the grammar from the tmp folder
    Grammar g = convert(argv[1]);

    printf("%p\n", g);
    // Display the Grammar
    display(g);

    first_calculation(g);

    return 0;
}
#include <stdio.h>
#include "converter/converter.h"
#include "config/functions_prototypes.h"

int main(int argc, char **argv)
{
    // Extracting the grammar from the tmp folder
    Grammar g = convert(argv[1]);

    // Display the Grammar
    display(g);

    return 0;
}
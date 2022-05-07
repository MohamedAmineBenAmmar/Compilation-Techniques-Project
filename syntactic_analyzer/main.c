#include <stdlib.h>
#include "./config/types.h"
#include "./converter/converter.h"

int main(int argc, char **argv)
{
    Grammar g;

    g = convert(argv[1]);

    return 0;
}
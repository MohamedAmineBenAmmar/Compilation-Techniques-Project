#include <stdio.h>
#include <string.h>

void jump(char *string)
{
    for (int i = strlen(string); i >= 0; i--)
    {
        string[i + 1] = string[i];
    }

    string[0] = (char)(((int)string[1]) + 1);
}

void rec_fn(char *string)
{
    char local[50];
    local[0] = '\0';

    strcpy(local, string);

    if (strlen(local) <= 5)
    {
        jump(local);
        rec_fn(local);
        printf("\n%s\n", local);
    }

}

int main(int argc, char **argv)
{

    char string[50] = "a";
    rec_fn(string);
    return 0;
}
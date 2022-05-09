#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "first.h"
#include "../../config/functions_prototypes.h"

void firstOf(Grammar main_node, Grammar secondary_node, Grammar g, SLL *firstOfArg, int *replace)
{
    char c;
    SLL sll_ptr;
    SLL sll_flag;
    char buffer[2];
    buffer[0] = ' ';
    buffer[1] = '\0';

    int index;

    index = 0;

    // printf("\nnon terminal: %s", secondary_node->nonTerminal);
    // scanf("%c", &c);

    sll_ptr = secondary_node->sll;
    while (sll_ptr != NULL)
    {

    check_point:
        // printf("index value %d\n", index);
        // printf("sll indexes %c\n", sll_ptr->string[index]);
        // scanf("%c", &c);

        buffer[0] = sll_ptr->string[index];
        int isNonTerminalFlag = isNonTerminal(g, buffer);

        printf("Buffer %s\n", buffer);
        scanf("%c", &c);
        if (isNonTerminalFlag == 0)
        {
            if (main_node == secondary_node)
            {
                sll_flag = sll_find(*firstOfArg, buffer);
                if (sll_flag == NULL)
                {
                    sll_append(firstOfArg, buffer, 0);
                }
            }
            else if ((main_node != secondary_node) && (buffer[0] != '@'))
            {
                sll_flag = sll_find(*firstOfArg, buffer);
                if (sll_flag == NULL)
                {
                    sll_append(firstOfArg, buffer, 0);
                }
            }
            else if ((main_node != secondary_node) && (buffer[0] == '@'))
            {
                *replace = 1;
            }
        }
        else
        {
            firstOf(main_node, find(g, buffer), g, firstOfArg, replace);
            if (*replace == 1)
            {
                *replace == 0;
                index++;
                if (index < strlen(sll_ptr->string))
                {
                    goto check_point;
                }
            }
        }

        sll_ptr = sll_ptr->next;
    }
}

First first_calculation(Grammar g)
{
    First first = NULL;
    First tmp_first = NULL;
    SLL sll;

    Grammar grammar_ptr = g;
    int replace = 0;

    char c;
    while (grammar_ptr != NULL)
    {
        sll = NULL;
        firstOf(grammar_ptr, grammar_ptr, g, &sll, &replace);
        append(&first, grammar_ptr->nonTerminal, sll);
        // display(first);

        // scanf("%c", &c);
        grammar_ptr = grammar_ptr->next;
    }

    return first;
}
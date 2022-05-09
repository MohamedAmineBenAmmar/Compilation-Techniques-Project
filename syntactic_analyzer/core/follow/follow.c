#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "follow.h"
#include "../../config/functions_prototypes.h"

void followOf(char nonTerminal, Grammar g, SLL *followOfArg, Follow f, First fst)
{
    Grammar grammar_ptr;
    SLL sll_ptr;
    SLL sll_node_adr;
    char *char_ptr;
    int char_ascii_code = (int)nonTerminal;
    int index;
    char buffer[2];
    int isNonTerminalFlag;
    Follow node_adr;

    buffer[0] = ' ';
    buffer[1] = '\0';

    grammar_ptr = g;
    while (grammar_ptr != NULL)
    {
        sll_ptr = grammar_ptr->sll;
        while (sll_ptr != NULL)
        {

            char_ptr = strchr(sll_ptr->string, char_ascii_code);
            index = char_ptr - (sll_ptr->string);
        check_point:
            if (index > -1)
            {
                // The nonTerminal exists within the string
                if (index == strlen(sll_ptr->string) - 1)
                {
                    // né5ou suivant bta3 el current production rule && le non terminal éli éna fih != different méli ncalculi fih
                    buffer[0] = nonTerminal;
                    if (strcmp(buffer, grammar_ptr->nonTerminal) != 0)
                    {
                        // Here we are going to take the follow of the currnet production rule grammar_ptr->nonTerminal
                        node_adr = find(f, grammar_ptr->nonTerminal);

                        // check if already calculated or not
                        if (node_adr == NULL)
                        {
                            followOf(grammar_ptr->nonTerminal[0], g, followOfArg, f, fst);
                        }
                        else
                        {
                            // Append the node_adr->sll (which represents the follow of the current production rule) to the follow of
                            // of the nonTerminal that we are calculating its follow
                            concat(followOfArg, node_adr->sll, 0);
                        }
                    }
                }
                else
                {
                    // Checking if sll->string[index +1] is terminal character or not
                    buffer[0] = sll_ptr->string[index + 1];
                    isNonTerminalFlag = isNonTerminal(g, buffer);
                    if (isNonTerminalFlag == 0)
                    {
                        // The character is a terminal character (take the character as it is)                        
                        sll_append(followOfArg, buffer);
                    }
                    else
                    {
                        // The character is a non terminal -> né5ou les premiers bté3ou oun testi est ce que epsilon appartien au premiers or not
                        node_adr = find(fst, buffer);

                        // Check if epsilon belongs to the first of that nonTerminal (node_adr->sll)
                        buffer[0] = '@';
                        sll_node_adr = sll_find(node_adr->sll, buffer);

                        if (sll_node_adr == NULL)
                        {
                            concat(followOfArg, node_adr->sll, 0);
                        }
                        else
                        {
                            concat(followOfArg, node_adr->sll, 1); // Don't allow epsilon to be added to the follow of our nonTerminal
                            index++;
                            goto check_point;
                        }
                    }
                }
            }
            sll_ptr = sll_ptr->next;
        }

        grammar_ptr = grammar_ptr->next;
    }
}

Follow follow_calculation(Grammar g, First fst)
{
    // char c;

    Grammar grammar_ptr;
    Follow f;
    SLL follow_sll;
    int head_flag = 1;

    char buffer[2];
    buffer[0] = '$';
    buffer[1] = '\0';

    grammar_ptr = g;
    f = NULL;
    while (grammar_ptr != NULL)
    {
        follow_sll = NULL;        
        // Adding dollar to the follow to first production rule
        if(head_flag == 1){
            sll_append(&follow_sll, buffer);
            head_flag = 0;            
        }

        followOf(grammar_ptr->nonTerminal[0], g, &follow_sll, f, fst);
        append(&f, grammar_ptr->nonTerminal, follow_sll);

        // printf("Debug \n");
        // display(f);
        // scanf("%c", &c);

        grammar_ptr = grammar_ptr->next;
    }

    return f;
}
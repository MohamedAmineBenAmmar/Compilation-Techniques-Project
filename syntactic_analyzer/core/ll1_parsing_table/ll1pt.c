#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ll1pt.h"
#include "../../config/functions_prototypes.h"

void split(Grammar grammar, SLL *terminals, SLL *nonTerminals)
{
    Grammar grammar_ptr;
    SLL sll_ptr;
    int isNonTerminalFlag;

    char buffer[2];
    buffer[0] = ' ';
    buffer[1] = '\0';

    *terminals = NULL;
    *nonTerminals = NULL;

    grammar_ptr = grammar;
    while (grammar_ptr != NULL)
    {
        // Adding the non terminal to the non terminal linked list
        sll_append(nonTerminals, grammar_ptr->nonTerminal, 0);

        // Adding the terminals to the terminals list
        sll_ptr = grammar_ptr->sll;
        while (sll_ptr != NULL)
        {
            for (size_t i = 0; i < strlen(sll_ptr->string); i++)
            {
                if (sll_ptr->string[i] == '@')
                {
                    continue;
                }

                buffer[0] = sll_ptr->string[i];

                isNonTerminalFlag = isNonTerminal(grammar, buffer);
                if (isNonTerminalFlag == 0)
                {
                    sll_append(terminals, buffer, 0);
                }
            }

            sll_ptr = sll_ptr->next;
        }

        grammar_ptr = grammar_ptr->next;
    }
}

void find_terminal(Grammar grammar, char *buffer, int level, char *terminal)
{
    Grammar node_adr;

    node_adr = find(grammar, buffer);
}

LL1PT ll1pt_constructor(Grammar grammar, First first, Follow follow)
{
    Grammar grammar_ptr;  // used to loop through the nonTerminals
    First firstOfCurrent; // used to hold the first of the current nonTerminal
    SLL track_list;
    Follow followOfCurrent; // used to hold the follow of the current nonTerminal
    SLL production_rule;    // used to loop through the current nonTerminal production rules
    BaseNode *node_adr;     // Flag used to hold an adress of BaseNode
    SLL sll_node_ptr;
    LL1PT ll1pt; // The head of the LL1 parsing table linked list
    LL1PT ll1pt_ptr;
    SLL ll1pt_sll;
    Follow follow_ptr;
    int isNonTerminalFlag, index;
    char buffer[2];
    char *correspond_terminal;
    int level;
    int size;

    char c;

    char tmp_terminal[2];
    tmp_terminal[0] = ' ';
    tmp_terminal[1] = '\0';

    // Init
    buffer[0] = ' ';
    buffer[1] = '\0';

    ll1pt = NULL;
    grammar_ptr = grammar;
    // ll1pt = (LL1PT)malloc(sizeof(LL1PTRow)); // Allocating the memory for the head of the linked list
    // ll1pt_ptr = ll1pt;
    while (grammar_ptr != NULL)
    {
        // Setting the LL1PT
        if (ll1pt == NULL)
        {
            ll1pt = (LL1PT)malloc(sizeof(LL1PTRow));
            ll1pt_ptr = ll1pt;
        }
        else
        {
            ll1pt_ptr->next = (LL1PT)malloc(sizeof(LL1PTRow));
            ll1pt_ptr = ll1pt_ptr->next;
        }

        // Init the sll for the current nonTerminal
        ll1pt_sll = NULL;
        track_list = NULL;

        // Get the first of the current nonTerminal
        firstOfCurrent = find(first, grammar_ptr->nonTerminal);

        // Get the follow of the current nonTermnial
        followOfCurrent = find(follow, grammar_ptr->nonTerminal);

        // Lopping through the production rules
        production_rule = grammar_ptr->sll;
        while (production_rule != NULL)
        {
            buffer[0] = production_rule->string[0];
            isNonTerminalFlag = isNonTerminal(grammar, buffer);
            if (isNonTerminalFlag == 0)
            {
                // The character is a terminal
                if (buffer[0] != '@')
                {
                    // Check if this character belongs to the first
                    sll_node_ptr = sll_find(firstOfCurrent->sll, buffer);

                    // If node_adr is not equal to null it means that the character belongs to the first of the current
                    // nonTerminal letter that we are working on
                    if (sll_node_ptr != NULL)
                    {
                        // Adding node to the LL1 parsing table linked list
                        sll_append(&ll1pt_sll, production_rule->string, 0);
                        sll_append(&track_list, buffer, 0);
                    }
                }
                else
                {
                    // Handling epsilon (check for the follow)
                    // Lopping through the follow of that nonTerminal @-> each one of them
                    // concat(&ll1pt_sll, , 0);
                    size = sll_length(followOfCurrent->sll);
                    for (size_t i = 0; i < size; i++)
                    {
                        sll_append(&ll1pt_sll, production_rule->string, 1);
                    }

                    concat(&track_list, followOfCurrent->sll, 0, 0);
                }
            }
            else
            {
                // The character is non terminal
                // Adding the produnction rule multiple times
                size = sll_length(firstOfCurrent->sll);
                for (size_t i = 0; i < size; i++)
                {
                    sll_append(&ll1pt_sll, production_rule->string, 1);
                }
                concat(&track_list, firstOfCurrent->sll, 0, 0);
            }
            production_rule = production_rule->next;
        }

        // printf("\nDEBUG\n");
        // printf("Non terminal: %s\n", grammar_ptr->nonTerminal);
        // printf("Keys: ");
        // display_sll(track_list);
        // printf("\n");
        // printf("PR: ");
        // display_sll(ll1pt_sll);
        // scanf("%c", &c);

        ll1pt_ptr->nonTerminal = (char *)malloc(strlen(grammar_ptr->nonTerminal) * sizeof(char));
        strcpy(ll1pt_ptr->nonTerminal, grammar_ptr->nonTerminal);

        ll1pt_ptr->keys = track_list;
        ll1pt_ptr->values = ll1pt_sll;

        grammar_ptr = grammar_ptr->next;
    }

    ll1pt_ptr->next = NULL;

    return ll1pt;
}

char *get_key_value_pair(LL1PT ll1pt, char *key)
{
    SLL sll_keys_ptr;
    SLL sll_values_ptr;

    char *value = NULL;

    sll_keys_ptr = ll1pt->keys;
    sll_values_ptr = ll1pt->values;
    while (sll_keys_ptr != NULL && sll_values_ptr != NULL)
    {
        if (strcmp(sll_keys_ptr->string, key) == 0)
        {
            value = (char *)malloc(strlen(sll_values_ptr->string) * sizeof(char));
            strcpy(value, sll_values_ptr->string);
            break;
        }
        sll_keys_ptr = sll_keys_ptr->next;
        sll_values_ptr = sll_values_ptr->next;
    }

    return value;
}

void display_ll1pt(LL1PT ll1pt, Grammar grammar)
{
    SLL terminals, nonTerminals;
    SLL sll_ptr;
    LL1PT ll1pt_ptr;
    char *value;

    split(grammar, &terminals, &nonTerminals);

    // Display the LL1 Table header
    printf("\n");
    printf("=====================================================================================================================");
    printf("\n");
    printf("                     |\t\t\t\t\t  Terminal Symbols  \t\t");
    printf("\n");    
    printf("=====================================================================================================================");
    printf("\n");

    printf("Non Terminal Symbols |\t");
    sll_ptr = terminals;
    while (sll_ptr != NULL)
    {
        printf("\t %s \t", sll_ptr->string);
        sll_ptr = sll_ptr->next;
    }
    printf("\n");
    printf("=====================================================================================================================");
    printf("\n");

    ll1pt_ptr = ll1pt;
    while (ll1pt_ptr != NULL)
    {
        printf("\t%s\t\t", ll1pt_ptr->nonTerminal);

        sll_ptr = terminals;
        while (sll_ptr != NULL)
        {
            value = get_key_value_pair(ll1pt_ptr, sll_ptr->string);
            if (value == NULL)
            {
                printf("\t  \t");
            }
            else
            {
                printf("\t%s->%s\t", ll1pt_ptr->nonTerminal, value);
            }

            sll_ptr = sll_ptr->next;
        }
        printf("\n");
        printf("=====================================================================================================================");
        printf("\n");

        ll1pt_ptr = ll1pt_ptr->next;
    }
}
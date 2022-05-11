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

void jumpBy(char *string, int n)
{
    for (int i = strlen(string); i >= 0; i--)
    {
        string[i + n] = string[i];
    }

    // string[0] = (char)(((int)string[1]) + 1);
}

void strSetAt(char *src, char *dest, int pos)
{
    int j = pos;
    for (size_t i = 0; i < strlen(src); i++)
    {
        dest[j] = src[i];
        j++;
    }
}

void find_production_rule(Grammar grammar,
                          char *production_rule, char *target_terminal,
                          int *rec_call_flag, int *epsilon_flag,
                          int rec_call_track)
{
    Grammar grammar_node;
    SLL sll_ptr;

    char local_large_buffer[256];
    local_large_buffer[0] = '\0';
    int index;
    index = 0;

    int isNonTerminalFlag;
    char buffer[2];
    buffer[0] = ' ';
    buffer[1] = '\0';

    strcpy(local_large_buffer, production_rule);

non_terminal_selection:
    buffer[0] = local_large_buffer[index];
    grammar_node = find(grammar, buffer);

    // Looping through the nonTerminal production rules
    sll_ptr = grammar_node->sll;
    while (sll_ptr != NULL)
    {
        buffer[0] = sll_ptr->string[0];
        isNonTerminalFlag = isNonTerminal(grammar, buffer);
        if (isNonTerminalFlag == 0)
        {
            // We get a terminal character
            // We must test if its the epsilon character or not
            if (buffer[0] == '@')
            {
                // Setting a flag variable to notify the recursive calls in the stack that
                // the current recursive finds an epsilon character
                // that will be substituted
                *epsilon_flag = 1;
                if (rec_call_track == 1)
                {
                    break;
                }
                else
                {
                    goto epsilon_check;
                }
            }
            else
            {
                if (strcmp(buffer, target_terminal) == 0)
                {
                    *rec_call_flag = 1; // Here we found the terminal needed (our target)
                    break;              // We must stop the other recursive calls that are waiting in the stack
                }
            }
        }
        else
        {
            // We get a nonTerminal character
            // Substiute the non terminal at the start of the production rule by the production rule that we got
            jumpBy(local_large_buffer, strlen(sll_ptr->string) - 1);
            strSetAt(sll_ptr->string, local_large_buffer, 0);

            // Making the recursive call
            find_production_rule(grammar, local_large_buffer, target_terminal, rec_call_flag, epsilon_flag, 1);

        epsilon_check:
            // Check if we hit an epslilon character or we did find the target terminal
            if (*epsilon_flag == 1)
            {
                *epsilon_flag = 0;
                if ((index + 1) < strlen(local_large_buffer))
                {
                    buffer[0] = local_large_buffer[index + 1];
                    if (isNonTerminal(grammar, buffer) == 1)
                    {
                        index++;
                        goto non_terminal_selection;
                    }
                }
            }

            // Check if we find the non terminal target
            if (*rec_call_flag == 1)
            {
                break;
            }
        }

        sll_ptr = sll_ptr->next;
    }
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
    int rec_call_flag, epsilon_flag;

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
                sll_node_ptr = firstOfCurrent->sll;
                while (sll_node_ptr != NULL)
                {
                    // Init all the variables needed by our recursive function
                    rec_call_flag = 0;
                    epsilon_flag = 0;
                    find_production_rule(grammar, production_rule->string, sll_node_ptr->string, &rec_call_flag, &epsilon_flag, 0);

                    if (rec_call_flag == 1)
                    {
                        sll_append(&ll1pt_sll, production_rule->string, 1);
                        sll_append(&track_list, sll_node_ptr->string, 0);
                    }
                    sll_node_ptr = sll_node_ptr->next;
                }
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

LL1PT find_ll1pt_row(LL1PT ll1pt, char *nonTerminal)
{
    LL1PT ptr, node_adr;

    node_adr = NULL;
    ptr = ll1pt;
    while (ptr != NULL)
    {
        if (strcmp(ptr->nonTerminal, nonTerminal) == 0)
        {
            node_adr = ptr;
            break;
        }

        ptr = ptr->next;
    }

    return node_adr;
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

void print_ll1pt_exploitation_row(StringStack stack, StringStack input, char *production_rule)
{
    printf("\t\t");
    print_stack(stack);
    printf("\t\t\t");
    print_stack(input);
    printf("\t\t\t ");
    printf("%s", production_rule);
    printf("\t\t");
    printf("\n");
    printf("------------------------------------------------------------------------------------");
    printf("\n");
}

void exploit_ll1pt(LL1PT ll1pt, Grammar grammar, char *word)
{
    StringStack stack = NULL, input = NULL, output = NULL;
    LL1PT ll1pt_row;
    char stack_item[2];
    char input_item[2];
    char *value;
    int isNonTerminalFlag;
    int status = 1;
    char production_rule[256];
    char derivation_arrow[] = "->";
    char lastNonTerminal[2];
    lastNonTerminal[0] = ' ';
    lastNonTerminal[1] = '\0';
    char dollar[2];
    dollar[0] = '$';
    dollar[1] = '\0';

    // Init
    input = push(input, dollar);
    stack = push(stack, dollar);

    stack = push(stack, ll1pt->nonTerminal);
    input = bulk_push(input, word);

    // Displaying the fist line of the stack
    printf("\n");
    printf("=====================================================================================");
    printf("\n");
    printf("\t\tStack \t\t\tInput\t\t\t Output\t\t");
    printf("\n");
    printf("=====================================================================================");
    printf("\n");

    production_rule[0] = '\0';
    print_ll1pt_exploitation_row(stack, input, production_rule);

    // Displaying the table content
    while (empty(stack) == 0 && empty(input) == 0)
    {
        strcpy(stack_item, peek(stack));
        strcpy(input_item, peek(input));
        production_rule[0] = '\0';

        isNonTerminalFlag = isNonTerminal(grammar, stack_item);
        if (isNonTerminalFlag == 1)
        {
            ll1pt_row = find_ll1pt_row(ll1pt, stack_item);
            value = get_key_value_pair(ll1pt_row, input_item);
            if (value == NULL)
            {
                // printf("Error");
                status = 0;
                break;
            }
            else
            {
                stack = pop(stack);
                stack = bulk_push(stack, value);

                strcat(production_rule, stack_item);
                strcat(production_rule, derivation_arrow);
                strcat(production_rule, value);

                print_ll1pt_exploitation_row(stack, input, production_rule);
            }

            strcpy(lastNonTerminal, stack_item);
        }
        else
        {
            if (stack_item[0] == '@')
            {
                stack = pop(stack);

                strcat(production_rule, lastNonTerminal);
                strcat(production_rule, derivation_arrow);
                strcat(production_rule, stack_item);

                print_ll1pt_exploitation_row(stack, input, production_rule);
            }
            else
            {
                if (strcmp(stack_item, input_item) == 0)
                {
                    stack = pop(stack);
                    input = pop(input);

                    // strcat(production_rule, lastNonTerminal);
                    // strcat(production_rule, derivation_arrow);
                    // strcat(production_rule, stack_item);
                    production_rule[0] = '\0';
                    print_ll1pt_exploitation_row(stack, input, production_rule);
                }
                else
                {
                    // printf("Error");
                    status = 0;
                    break;
                }
            }
        }

    }

    printf("\n");
    printf("==> ");
    if(status == 0){
        printf("Error occured word is not accepted !!!");
        printf("\n");
    } else {
        printf("Success, word accepted.");
        printf("\n");
    }
    printf("====================================================================================");
    printf("\n");
}

void display_ll1pt(LL1PT ll1pt, Grammar grammar)
{
    SLL terminals, nonTerminals;
    SLL sll_ptr;
    LL1PT ll1pt_ptr;
    char *value;

    char dollar[2];
    dollar[0] = '$';
    dollar[1] = '\0';

    split(grammar, &terminals, &nonTerminals);
    sll_append(&terminals, dollar, 0);

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
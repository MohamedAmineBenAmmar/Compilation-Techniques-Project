#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions_prototypes.h"

void display(BaseNode *head)
{
    BaseNode *ptr;
    SLL tmp_sll_ptr;

    ptr = head;
    while (ptr != NULL)
    {
        // printf("%s %d", ptr->nonTerminal, strlen(ptr->nonTerminal));
        printf("%s", ptr->nonTerminal);
        printf(" -> ");
        tmp_sll_ptr = ptr->sll;
        while (tmp_sll_ptr != NULL)
        {
            // printf("%s %d", tmp_sll_ptr->string, strlen(tmp_sll_ptr->string));
            printf("%s", tmp_sll_ptr->string);
            if (tmp_sll_ptr->next != NULL)
            {
                printf(" | ");
            }

            tmp_sll_ptr = tmp_sll_ptr->next;
        }

        printf("\n");

        ptr = ptr->next;
    }
}

BaseNode *find(BaseNode *head, char *nonTerminal)
{
    BaseNode *node_adr = NULL, *ptr;

    ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(nonTerminal, ptr->nonTerminal) == 0)
        {
            node_adr = ptr;
            break;
        }

        ptr = ptr->next;
    }

    return node_adr;
}

int sll_length(SLL head)
{
    int length = 0;
    SLL ptr;

    ptr = head;
    while (ptr != NULL)
    {
        length++;
        ptr = ptr->next;
    }

    return length;
}

SLL sll_find(SLL head, char *string)
{
    SLL node_adr, ptr;

    node_adr = NULL;
    ptr = head;

    while (ptr != NULL)
    {
        if (strcmp(string, ptr->string) == 0)
        {
            node_adr = ptr;
            break;
        }

        ptr = ptr->next;
    }

    return node_adr;
}

void append(BaseNode **head, char *nonTerminal, SLL sll)
{

    BaseNode *ptr;
    BaseNode *new_node = (BaseNode *)malloc(sizeof(BaseNode));

    // Setting the nonTerminal
    new_node->nonTerminal = (char *)malloc(strlen(nonTerminal) * sizeof(char));
    strcpy(new_node->nonTerminal, nonTerminal);

    // Setting the next of the new node to NULL
    new_node->next = NULL;

    // Setting the list of strings
    new_node->sll = sll;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        ptr = *head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }

        ptr->next = new_node;
    }
}

SLL sll_constructor()
{
    SLL head = NULL;
    return head;
}

void display_sll(SLL head)
{
    SLL ptr;

    ptr = head;
    while (ptr != NULL)
    {
        // printf("%s: %d  ", ptr->string, strlen(ptr->string));
        printf("%s  ", ptr->string);
        ptr = ptr->next;
    }

    printf("\n");
}

void sll_append(SLL *head, char *string, int allow_duplicate_values)
{
    SLL ptr, new_node, node_adr;

    node_adr = sll_find(*head, string);
    if (node_adr == NULL || allow_duplicate_values == 1)
    {
        new_node = (SLL)malloc(sizeof(StringLinkedListNode));

        new_node->string = (char *)malloc(strlen(string) * sizeof(char));
        strcpy(new_node->string, string);
        new_node->next = NULL;

        if (*head == NULL)
        {
            *head = new_node;
        }
        else
        {
            ptr = *head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }

            ptr->next = new_node;
        }
    }
}

void concat(SLL *dest, SLL src, int epsilon_flag, int allow_duplicate_values)
{
    SLL sll_ptr;

    sll_ptr = src;
    while (sll_ptr != NULL)
    {
        if (!((epsilon_flag == 1) && (sll_ptr->string[0] == '@')))
        {
            sll_append(dest, sll_ptr->string, allow_duplicate_values);
        }

        sll_ptr = sll_ptr->next;
    }
}

int isNonTerminal(Grammar g, char *string)
{
    int result = 0;
    BaseNode *grammar_ptr = g;

    while (grammar_ptr != NULL)
    {
        if (strcmp(grammar_ptr->nonTerminal, string) == 0)
        {
            result = 1;
            break;
        }

        grammar_ptr = grammar_ptr->next;
    }

    return result;
}

// Developing the stack functions methods
StringStack push(StringStack head, char *string)
{
    StringStack new_node;

    new_node = (StringStack)malloc(sizeof(StringLinkedListNode));
    new_node->string = (char *)malloc(strlen(string) * sizeof(char));
    strcpy(new_node->string, string);
    new_node->next = head;

    return new_node;
}

StringStack pop(StringStack head)
{
    StringStack ptr;

    ptr = head->next;
    free(head->string);
    free(head);
    return ptr;
}

char *peek(StringStack head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        return head->string;
    }
}

int empty(StringStack head)
{
    if (head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
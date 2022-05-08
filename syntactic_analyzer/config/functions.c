#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions_prototypes.h"

void display(BaseNode *head)
{
    BaseNode *ptr;
    SLL tmp_sll_ptr;

    ptr = head;
    printf("Content:\n");
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

void sll_append(SLL *head, char *string)
{
    SLL ptr, new_node;

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

int isNonTerminal(Grammar g, char* string)
{
    int result = 0;
    BaseNode *grammar_ptr = g;

    while (grammar_ptr != NULL)
    {
        if(strcmp(grammar_ptr->nonTerminal, string) == 0){
            result = 1;
            break;
        }

        grammar_ptr = grammar_ptr->next;
    }
    
    return result;
}
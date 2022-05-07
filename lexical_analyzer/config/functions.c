#include "functions_prototypes.h"
#include "string.h"
#include "stdlib.h"

void add_word(WL *head_ptr , char *new_word)
{
    WL ptr;

    ptr = (WL)malloc(sizeof(WLNode));
    strcpy(ptr->word, new_word);
    ptr->next = *head_ptr;
    *head_ptr = ptr;
}

WL extract_words(char* fileName)
{
   int i;
    FILE *file = fopen(fileName, "r"); /* should check the result */
    char line[10];

    // Init the head of the linked list
    WL head = NULL;

    if (!file)
    {
        printf("\n Unable to open : %s ", fileName);
        return NULL;
    }


    while (fgets(line, sizeof(line), file))
    {
        // Skip comments and empty lines
        /* 
        line_verification_status = verify_line(line);
        if (line_verification_status == 0)
        {
            continue;
        }
        */

        // Add the word to the linked list
        // printf("Line: %s\n", line);
        // scanf("%d", &i);
        line[strlen(line) -1] = '\0';
        add_word(&head, line);
    }

    fclose(file);

    return head;
}

void display_words_list(WL head, char *msg){
    WL ptr;
    ptr = head;

    printf("%s\n", msg);
    while (ptr != NULL)
    {
        printf("%s    ", ptr->word);
        ptr = ptr->next;
    }
    printf("\n");
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "converter.h"

Grammar convert(char *filePath)
{
    FILE *filePointer;
    char buffer[255];
    char tmpBuffer[255];
    int buffer_size;
    char ch;

    int arrow_flag;
    int arrow_flag_detecter;
    int nonTerminal_flag;

    Grammar g, ptr;
    SLL tmp_sll_ptr;

    // Initial configuration
    buffer[0] = '\0';
    buffer_size = 0;

    arrow_flag_detecter = 0;
    arrow_flag = 0;
    nonTerminal_flag = 0;

    // Open the file and read its content character by character
    filePointer = fopen(filePath, "r");
    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        // Handling the head of the Grammar linked list
        g = (Grammar)malloc(sizeof(BaseNode));
        g->sll = NULL;        
        ptr = g;
        // -------

        while ((ch = fgetc(filePointer)) != EOF)
        {
            if (ch == '\n')
            {
                // Allocating the needed memory for the new GrammarNode + Handling nodes linking
                ptr->next = (Grammar)malloc(sizeof(BaseNode));                
                ptr = ptr->next;
                ptr->sll = NULL;                
                // -------

                buffer[0] = '\0';
                buffer_size = 0;
                arrow_flag_detecter = 0;
                arrow_flag = 0;
                nonTerminal_flag = 0;
            }
            else
            {
                if (nonTerminal_flag == 0 && arrow_flag == 1)
                {
                    // Setting the non terminal
                    ptr->nonTerminal = (char *)malloc((buffer_size-2) * sizeof(char));
                    strncpy(tmpBuffer, buffer, (buffer_size-2));
                    strcpy(ptr->nonTerminal, tmpBuffer);
                    ptr->nonTerminal[buffer_size -2] = '\0';
                    // ---------

                    buffer[0] = '\0';
                    buffer_size = 0;

                    nonTerminal_flag = 1;
                }

                if (nonTerminal_flag == 0)
                {
                    // Directly concatenate the characters
                    strncat(buffer, &ch, 1);
                    buffer_size++;

                    // Schearing for the arrow that seperates the non terminal from the production rules
                    if (ch == '-')
                    {
                        arrow_flag_detecter = 1;
                    }
                    else if (ch == '>' && arrow_flag_detecter == 1)
                    {
                        arrow_flag = 1;
                    }
                    else if (ch != '>' && arrow_flag_detecter == 1)
                    {
                        arrow_flag_detecter = 0;
                    }
                }
                else
                {
                    if (ch == '|')
                    {
                        // Handliing adding new production rule to the string linked list inside the grammar node
                        if(ptr->sll == NULL){
                            // Setting the head of string linked list
                            ptr->sll = (SLL)malloc(sizeof(StringLinkedListNode));

                            // Allocating memory for the string
                            ptr->sll->string = (char *)malloc((buffer_size) * sizeof(char));
                            strcpy(ptr->sll->string, buffer);
                            ptr->sll->string[buffer_size] = '\0';                            
                            ptr->sll->next = NULL;
                        } else {
                            // Addiong nodes at the tail of the linked list
                            tmp_sll_ptr = ptr->sll;
                            while (tmp_sll_ptr->next != NULL)
                            {
                                tmp_sll_ptr = tmp_sll_ptr->next;
                            }

                            tmp_sll_ptr->next = (SLL)malloc(sizeof(StringLinkedListNode));
                            tmp_sll_ptr = tmp_sll_ptr->next;

                            tmp_sll_ptr->string = (char *)malloc((buffer_size) * sizeof(char));
                            strcpy(tmp_sll_ptr->string, buffer);    
                            tmp_sll_ptr->string[buffer_size] = '\0';                        
                            tmp_sll_ptr->next = NULL;
                        }
                        // -----

                        buffer[0] = '\0';
                        buffer_size = 0;
                    }
                    else
                    {
                        // Concatenate the character
                        strncat(buffer, &ch, 1);
                        buffer_size++;
                    }
                }
            }
        }

        ptr->next = NULL;
    }

    fclose(filePointer);

    return g;
}
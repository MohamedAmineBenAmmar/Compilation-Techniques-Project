#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "converter.h"

Grammar convert(char *filePath)
{
    FILE *filePointer;
    char buffer[255];
    int buffer_size;
    char ch;

    int arrow_flag;
    int arrow_flag_detecter;
    int nonTerminal_flag;

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

        // -------

        // Setting up the pointer inter pointer that is going to be used later on

        // -------
        while ((ch = fgetc(filePointer)) != EOF)
        {
            if (ch == '\n')
            {
                // Allocating the needed memory for the new GrammarNode + Handling nodes linking

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
    }

    fclose(filePointer);
}
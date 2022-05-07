#include "minifier.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *minify(char *filePath)
{
    FILE *fileToReadPointer, *fileToWritePointer;
    char ch;

    int dot = '.';
    int slash = '/';
    char EOP = '$';
    char *dot_ptr;
    char *slash_ptr;
    char newFileName[100];
    char fileName[100];
    char fileExtension[10];
    char *newFilePath = (char *)malloc(255 * sizeof(char));

    int msg_flag = 0;

    // Determining the new file name which is going to hold the
    // minified src code
    slash_ptr = strrchr(filePath, slash);
    strncpy(fileName, &filePath[(slash_ptr - filePath) + 1], strlen(filePath) - (slash_ptr - filePath) + 1);

    dot_ptr = strchr(fileName, dot);
    if (dot_ptr - fileName > -1)
    {
        strncpy(newFileName, fileName, (dot_ptr - fileName));
        strcat(newFileName, "_minified.");
        strncpy(fileExtension, &fileName[(dot_ptr - fileName) + 1], strlen(fileName) - (dot_ptr - fileName) + 1);

        strcpy(newFilePath, "lexical_analyzer/tmp/minified_src_code/");
        strcat(newFilePath, newFileName);
        strcat(newFilePath, fileExtension);
    }
    fileToReadPointer = fopen(filePath, "r");
    fileToWritePointer = fopen(newFilePath, "w");

    if (fileToReadPointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        while ((ch = fgetc(fileToReadPointer)) != EOF)
        {
            if (msg_flag == 0)
            {
                if (ch != ' ' && ch != '\n')
                {
                    putc(ch, fileToWritePointer);
                }

                if(ch == '"'){
                    msg_flag = 1;
                }
            } else {
                if (ch != '\n')
                {
                    putc(ch, fileToWritePointer);
                }

                if(ch == '"'){
                    msg_flag = 0;
                }
            }
        }
    }

    putc(EOP, fileToWritePointer);
    fclose(fileToReadPointer);
    fclose(fileToWritePointer);

    return newFilePath;
}
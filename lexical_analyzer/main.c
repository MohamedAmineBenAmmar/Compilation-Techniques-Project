#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./config/functions_prototypes.h"
#include "./tokens/tokens.h"

#include "./preprocessor/minifier/minifier.h"

int main(int argc, char **argv)
{
    // Decalaring the variables needed
    char word[256];
    char lexical_unit[10];
    int word_length;
    WL keywords_list = NULL,
       logical_operators_list = NULL,
       relational_operators_list = NULL,
       separators_list = NULL,
       functions_list = NULL;

    // Init
    word[0] = '\0';
    word_length = 0;

    int predict_separation_flag;
    char sep_buffer[2];
    sep_buffer[0] = ' ';
    sep_buffer[1] = '\0';

    // DEBUG
    char test;
    // DEBUG

    keywords_list = extract_words("lexical_analyzer/config/files/keywords.txt");
    // display_words_list(keywords_list, "Keywords List");

    logical_operators_list = extract_words("lexical_analyzer/config/files/logical_operators.txt");
    // display_words_list(logical_operators_list, "Logical Operators List");

    relational_operators_list = extract_words("lexical_analyzer/config/files/relational_operators.txt");

    // display_words_list(relational_operators_list, "Relational Operators List");

    separators_list = extract_words("lexical_analyzer/config/files/separators.txt");
    // display_words_list(separators_list, "Separators List");

    functions_list = extract_words("lexical_analyzer/config/files/functions.txt");

    // Minify the user code
    char *newFilePath = minify(argv[1]);

    // Reading the minified source code charcter by character, build a word and then classify it
    FILE *filePointer;
    char ch;
    int msg_flag = 0;

    filePointer = fopen(newFilePath, "r");
    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        while ((ch = fgetc(filePointer)) != EOF)
        {
            // Concatenate the character to the current word
            strncat(word, &ch, 1);
            word_length++;

            // printf("word: %s\n", word);
            // scanf("%c", &test);

            // Handling the messages
            if (msg_flag == 0)
            {
                if (word[0] == '"')
                {
                    msg_flag = 1;
                    continue;
                }
            }
            else
            {
                if (ch == '"')
                {
                    msg_flag = 0;
                }
                else
                {
                    continue;
                }
            }

            // Classify the word
            strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
            if (strcmp(lexical_unit, "real") != 0 && strcmp(lexical_unit, "number") != 0 && strcmp(lexical_unit, "id") != 0 && strcmp(lexical_unit, "undefined") != 0)
            {
                // printf("1\n");
                printf("%s : %s\n", word, lexical_unit);

                word[0] = '\0';
                word_length = 0;
            }
            else
            {
                // printf("2\n");
                sep_buffer[0] = ch;
                strcpy(lexical_unit, classify(sep_buffer, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
                if (strcmp(lexical_unit, "sep") == 0)
                {
                    word[strlen(word) - 1] = '\0';
                    strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
                    printf("%s : %s\n", word, lexical_unit);

                    printf("%s : sep\n", sep_buffer);

                    word[0] = '\0';
                    word_length = 0;
                }
                else
                {
                    if (predict_separation_flag == 1)
                    {
                        predict_separation_flag = 0;
                        strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
                        if (strcmp(lexical_unit, "undefined") == 0)
                        {
                            word[strlen(word) -1] = '\0';
                            strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
                            printf("%s : %s\n", word, lexical_unit);

                            word[0] = ch;
                            word[1] = '\0';
                            word_length = 1;
                        }  
                    }
                    else
                    {
                        // Predection of an operator
                        if (predict_separation(ch, logical_operators_list) == 1 || predict_separation(ch, relational_operators_list) == 1)
                        {
                            // printf("d5alt");
                            word[strlen(word) - 1] = '\0';
                            strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
                            printf("%s : %s\n", word, lexical_unit);

                            word[0] = ch;
                            word[1] = '\0';
                            word_length = 1;

                            predict_separation_flag = 1;
                        }
                    }
                }
            }
        }
    }

    fclose(filePointer);

    return 0;
}
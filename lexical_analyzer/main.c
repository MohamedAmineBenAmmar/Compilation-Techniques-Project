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
            strncat(word, &ch, 1);
            word_length++;

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

            // Determining the word nature
            // Determine the lexical unit in wich the string belongs
            strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));

            if (strcmp(lexical_unit, "keyword") == 0 || strcmp(lexical_unit, "msg") == 0)
            {
                printf("%s : %s\n", word, lexical_unit);

                word[0] = '\0';
                word_length = 0;    
            }
            else if (strcmp(lexical_unit, "undefined") == 0)
            {
                if (strlen(word) > 1)
                {
                    word[word_length - 1] = '\0';
                    strcpy(lexical_unit, classify(word, keywords_list, separators_list, logical_operators_list, relational_operators_list, functions_list));
                    printf("%s : %s\n", word, lexical_unit);
                }

                word[0] = ch;
                word[1] = '\0';
                word_length = 1;
            }
        }
    }

    fclose(filePointer);

    return 0;
}
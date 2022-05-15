#include "tokens.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"


int predict_separation(char c, WL words_list){
    int res = 0;
    WL ptr;
    while (ptr != NULL)
    {
        if(c == ptr->word[0]){
            res = 1;
            break;
        }
        ptr = ptr->next;
    }

    return res;
    
}

int isFraction(char *word)
{
    int result = 1;

    if (strlen(word) >= 2)
    {
        if (word[0] != '.')
        {
            result = 0;
        }
        else
        {
            for (size_t i = 1; i < strlen(word); i++)
            {
                if (!isdigit(word[i]))
                {
                    result = 0;
                    break;
                }
            }

            // Checking the size of the fraction part if it exceeded 10 chars
            // ........
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

int isCharacter(char c)
{
    int character_ascii_code = (int)c;

    if ((character_ascii_code >= 65 && character_ascii_code <= 90) || (character_ascii_code >= 97 && character_ascii_code <= 122))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isMessage(char *word)
{
    if (word[0] == '"' && word[strlen(word) - 1] == '"')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isIdentifier(char *word)
{
    int result = 1;

    if (strlen(word) >= 1)
    {
        if (isCharacter(word[0]) == 0 && word[0] != '_')
        {
            result = 0;
        }
        else
        {
            for (size_t i = 1; i < strlen(word); i++)
            {
                if (isCharacter(word[i]) == 0 && isdigit(word[i]) == 0 && word[i] != '_')
                {
                    result = 0;
                    break;
                }
            }
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

int isNumber(char *word)
{
    int result = 1;

    if (strlen(word) >= 1)
    {
        for (size_t i = 0; i < strlen(word); i++)
        {
            if (!isdigit(word[i]))
            {
                result = 0;
                break;
            }
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

int isReal(char *word)
{
    // char *string = "qwerty";
    char *dot;
    int index, result = 1, number_result, fraction_result;
    char integer_part[256];
    char fractional_part[256];

    dot = strchr(word, '.');
    index = (int)(dot - word);

    if (index < 0)
    {
        result = 0;
    }
    else
    {
        strncpy(integer_part, word, index);
        strcpy(fractional_part, &word[index]);

        // printf("integer part: %s %d\n", integer_part, strlen(integer_part));
        // printf("float part: %s %d", fractional_part, strlen(fractional_part));
        number_result = isNumber(integer_part);
        fraction_result = isFraction(fractional_part);
        if (!(number_result == 1 && fraction_result == 1))
        {
            result = 0;
        }
    }

    return result;
}

int find_word(char *word, WL words_list)
{
    WL ptr = words_list;
    int result = 0;
    while (ptr != NULL)
    {
        if (strcmp(ptr->word, word) == 0)
        {
            result = 1;
            break;
        }
        ptr = ptr->next;
    }

    return result;
}

int isKeyword(char *word, WL keywords_list)
{
    return find_word(word, keywords_list);
}

int isSeparator(char *word, WL separators_list)
{
    return find_word(word, separators_list);
}

int isLogicalOperator(char *word, WL operators_list)
{
    return find_word(word, operators_list);
}

int isRelationalOperator(char *word, WL relational_operators_list)
{
    return find_word(word, relational_operators_list);
}

int isFunction(char *word, WL functions_list)
{
    return find_word(word, functions_list);
}

char *classify(char *word, WL keywords_list, WL separators_list, WL logical_operators_list, WL relational_operators_list, WL functions_list)
{
    // char result[20];
    char *result = (char *)malloc(20 * sizeof(char));

    if (isKeyword(word, keywords_list) == 1)
    {
        strcpy(result, "keyword");
    }
    else if (isFunction(word, functions_list) == 1)
    {
        strcpy(result, "function");
    }
    else if (isSeparator(word, separators_list) == 1)
    {
        strcpy(result, "sep");
    }
    else if (isLogicalOperator(word, logical_operators_list) == 1)
    {
        strcpy(result, "log_op");
    }
    else if (isRelationalOperator(word, relational_operators_list) == 1)
    {
        strcpy(result, "rel_op");
    }
    else if (isMessage(word) == 1)
    {
        strcpy(result, "msg");
    }
    else if (isIdentifier(word) == 1)
    {
        strcpy(result, "id");
    }
    else if (isNumber(word) == 1)
    {
        strcpy(result, "number");
    }
    else if (isReal(word) == 1)
    {
        strcpy(result, "real");
    }
    else
    {
        strcpy(result, "undefined");
    }

    return result;
}
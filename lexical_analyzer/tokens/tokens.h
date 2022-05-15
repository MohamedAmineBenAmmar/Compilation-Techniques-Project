#ifndef TOKENS_HEADER_FILE
#define TOKENS_HEADER_FILE

#include "../config/types.h"

int isFraction(char *word); // Done
int isIdentifier(char *word); // Done
int isNumber(char *word); // Done
int isReal(char *word); // Done
int isMessage(char *word);
int isKeyword(char *word, WL keywords_list); // Done
int isSeparator(char *word, WL separators_list); // Done
int isLogicalOperator(char *word, WL logical_operators_list); // Done
int isRelationalOperator(char *word, WL relational_operators_list); // Done
int isFunction(char *word, WL functions_list);


int predict_separation(char c, WL words_list);
char *classify(char *word, WL keywords_list, WL separators_list, WL operators_list, WL relational_operators_list, WL functions_list);

#endif
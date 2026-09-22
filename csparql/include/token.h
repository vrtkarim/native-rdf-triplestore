#ifndef TOKEN_H
#include <stdbool.h>
typedef enum
{
    TOKEN_SELECT,
    TOKEN_WHERE,
    TOKEN_VARIABLE,
    TOKEN_IRI,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_DOT,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;
typedef struct
{
    TokenType type;
    char *text;
} Token;
void parseQuery(char* query); 
void getToken(unsigned int current, unsigned int index, char *query);
bool startsWith(char *token, char start);
bool endsWith(char *token, char end);
#endif
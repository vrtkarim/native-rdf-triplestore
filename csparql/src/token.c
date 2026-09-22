#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

void parseQuery(char *query)
{
    unsigned int current = 0;
    for (size_t index = 0; index < strlen(query) + 1; index++)
    {
        if (query[index] == ' ' || query[index] == '\0')
        {
            getToken(current, index, query);
            current = index + 1;
        }
    }
}
void getToken(unsigned int current, unsigned int index, char *query)
{
    size_t length = index - current;
    char *token = malloc((length + 1) * sizeof(*token));

    if (token == NULL)
    {
        return;
    }

    memcpy(token, query + current, length);
    token[length] = '\0';

    if (strcmp("SELECT", token) == 0)
    {
        /*  printf(" select from index %u, to index %u.", current, index); */
    }
    if (startsWith(token, '?'))

    {
        printf("token %s is a variable.\n", token);
    }
    if (startsWith(token, '<'))
    {
        printf("token %s is a IRI.\n", token);
    }
    if (startsWith(token, '.'))
    {
        printf("token %s is a dot.\n", token);
    }
    if (startsWith(token, '{'))
    {
        printf("left brace\n");
    }

    if (endsWith(token, '}'))
    {
        printf("right brace\n");
    }

    free(token);
}
bool startsWith(char *token, char start)
{
    if (token == NULL)
    {
        return false;
    }
    if (start == token[0])
    {
        return true;
    }
    return false;
}
bool endsWith(char *token, char end)
{
    if (token == NULL)
    {
        return false;
    }
    size_t length = strlen(token);
    if (end == token[length - 1])
    {
        return true;
    }
    return false;
}
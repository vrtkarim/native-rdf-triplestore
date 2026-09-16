#include "triplestore.h"

unsigned int hash(const char *str)
{
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * 31 + *str;
        str++;
    }

    return hash;
}
#ifndef TRIPLESTORE_H
#define TRIPLESTORE_H

#include <stddef.h>
#include <stdint.h>
#include "dictionary.h"

typedef struct
{
    uint32_t subject;
    uint32_t predicate;
    uint32_t object;
} Triple;

typedef struct Triplestore
{
    Dictionary *dictionary;
    Triple *triples;
    size_t size;
    size_t capacity;
} Triplestore;

/* Triple store functions */

Triplestore *create(void);
void triplestore_free(Triplestore *ts);
void insert(Triplestore *ts, const char *s, const char *p, const char *o);
int count(Triplestore *ts);

#endif

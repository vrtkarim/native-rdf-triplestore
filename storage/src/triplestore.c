#include "triplestore.h"
#include <stdlib.h>

#define DICTIONARY_CAPACITY 10
#define INITIAL_TRIPLE_CAPACITY 10

Triplestore *create(void)
{
    Triplestore *ts = malloc(sizeof(Triplestore));

    if (ts == NULL)
    {
        return NULL;
    }

    ts->dictionary = dictionary_create(DICTIONARY_CAPACITY);
    if (ts->dictionary == NULL)
    {
        free(ts);
        return NULL;
    }

    ts->triples = malloc(
        INITIAL_TRIPLE_CAPACITY * sizeof(Triple));
    if (ts->triples == NULL)
    {
        dictionary_free(ts->dictionary);
        free(ts);
        return NULL;
    }

    ts->size = 0;
    ts->capacity = INITIAL_TRIPLE_CAPACITY;

    return ts;
}

void insert(
    Triplestore *ts,
    const char *s,
    const char *p,
    const char *o)
{
    if (ts == NULL || s == NULL || p == NULL || o == NULL)
    {
        return;
    }

    uint32_t subject = dictionary_get_id(ts->dictionary, s);
    uint32_t predicate = dictionary_get_id(ts->dictionary, p);
    uint32_t object = dictionary_get_id(ts->dictionary, o);

    if (subject == 0 || predicate == 0 || object == 0)
    {
        return;
    }

    if (ts->size == ts->capacity)
    {
        size_t new_capacity = ts->capacity * 2;
        Triple *new_triples = realloc(
            ts->triples,
            new_capacity * sizeof(Triple));

        if (new_triples == NULL)
        {
            return;
        }

        ts->triples = new_triples;
        ts->capacity = new_capacity;
    }

    ts->triples[ts->size].subject = subject;
    ts->triples[ts->size].predicate = predicate;
    ts->triples[ts->size].object = object;
    ts->size++;
}

int count(Triplestore *ts)
{
    if (ts == NULL)
    {
        return 0;
    }

    return (int)ts->size;
}

void triplestore_free(Triplestore *ts)
{
    if (ts == NULL)
    {
        return;
    }

    dictionary_free(ts->dictionary);
    free(ts->triples);
    free(ts);
}
#include "triplestore.h"

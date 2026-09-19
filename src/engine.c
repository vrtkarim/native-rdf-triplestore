#include "triplestore.h"
#include "fetcher.h"
#include "hashtable.h"
#include "engine.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
/* the sv means that is the subject a variable */
#define TRIPLES_CAPACITY 10
Results *getTriples(Triplestore *ts, char *subject, char *predicate, char *object, bool sv, bool pv, bool ov)
{
    Triple *data = ts->triples;
    HashTable *ht = ts->dictionary->ht;
    uint32_t subjectt;
    uint32_t objectt;
    uint32_t predicatet;
    Results *results = malloc(sizeof(Results *));
    results->triples = malloc(sizeof(Triple *));
    results->size = 0;
    results->capacity = TRIPLES_CAPACITY;

    if (!sv)
    {
        subjectt = hashtable_find(ht, subject)->value;
    }
    if (!pv)
    {
        predicatet = hashtable_find(ht, predicate)->value;
    }
    if (!ov)
    {
        objectt = hashtable_find(ht, object)->value;
    }
    if (sv && pv && ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            addToTriples(results, ts->triples[i]);
        }
    }
    if (!sv && pv && ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            /* return triple where the subject match the subject*/
            if (subjectt == ts->triples[i].subject)
            {
                addToTriples(results, ts->triples[i]);
            }
        }
    }
    if (sv && !pv && ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            /* return triple where the predicate match the predicate*/
            if (predicatet == ts->triples[i].predicate)
            {
                printf("(%u, %u, %u)\n", ts->triples[i].subject, ts->triples[i].predicate, ts->triples[i].object);
                addToTriples(results, ts->triples[i]);
            }
        }
    }
    if (sv && pv && !ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            /* return triple where the object match the object*/
            if (objectt == ts->triples[i].object)
            {
                addToTriples(results, ts->triples[i]);
            }
        }
    }
    if (!sv && !pv && ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            /* return triple where the subject match the subject, also the predicate match the predicate*/
            if (subjectt == ts->triples[i].subject &&
                predicatet == ts->triples[i].predicate)
            {
                addToTriples(results, ts->triples[i]);
            }
        }
    }
    if (!sv && pv && !ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            /* return triple where the subject match the subject, also the object match the object*/
            if (subjectt == ts->triples[i].subject &&
                objectt == ts->triples[i].object)
            {
                addToTriples(results, ts->triples[i]);
            }
        }
    }
    if (sv && !pv && !ov)
    {
        for (size_t i = 0; i < count(ts); i++)
        {
            /* return triple where the predicate match the predicate, also the object match the object*/
            if (predicatet == ts->triples[i].predicate &&
                objectt == ts->triples[i].object)
            {
                addToTriples(results, ts->triples[i]);
            }
        }
    }
    return results;
}
bool triples_grow(Results *results)
{
    size_t newcapacity = results->capacity + TRIPLES_CAPACITY;
    Triple *new = realloc(results->triples, newcapacity * sizeof(Triple *));
    /* array size 1, zdtilo 2   0 1 2 , size 3, */
    if (new != NULL)
    {
        results->triples = new;
        results->capacity += TRIPLES_CAPACITY;
        free(new);
        return true;
    }
    else
    {
        return false;
    }
}
void addToTriples(Results *results, Triple triple)
{
    results->triples[results->size] = triple;
    results->size += 1;
    printf("size of triples in engine: %u\n", results->size);
    if (results->size >= results->capacity)
    {
        if (triples_grow(results))
        {
            /* code */
        }
        else
        {
            return;
        }
    }
}
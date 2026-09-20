#ifndef FETCHER_H
#define FETCHER_H

#include "triplestore.h" /* only for the Triple typedef */

typedef struct TripleChars
{
    char *s;
    char *p;
    char *o;
} TripleChars;
/* Read a Turtle/N-Triples file from disc.
 * Returns a malloc'd array of triples with *count set, or NULL on failure.
 * The strings are owned by the array. Release everything with fetch_free(). */
TripleChars *fetch_TripleChars(const char *path, int *count);

/* Free an array returned by fetch_triples. Safe on NULL. */
void fetch_free(TripleChars *triples, int count);

#endif
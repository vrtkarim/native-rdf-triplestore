#define triplestore
#include <stdint.h>
#include <stddef.h>

typedef struct Triplestore Triplestore;
typedef struct
{
    const uint32_t *s, *p, *o;
} Triple;

/* Triple store functions */

Triplestore *create(void);
void triplestore_free(Triplestore *ts);
void insert(Triplestore *ts, const char *s, const char *p, const char *o);
int count(Triplestore *ts);

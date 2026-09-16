#define triplestore
#include <stdint.h>
#include <stddef.h>

typedef struct Triplestore Triplestore;
typedef struct
{
    const uint32_t *s, *p, *o;
} Triple;

typedef struct
{
    char *key;
    uint32_t value;
} Entry;

typedef struct
{
    Entry *buckets[100];
    
} HashTable;

typedef struct
{
    HashTable *hashtable;

    char **id_to_string;

    size_t size;
    size_t capacity;
} Dictionary;

/* Triple store functions */

Triplestore *create(void);
void free(Triplestore *ts);
void insert(Triplestore *ts, const char *s, const char *p, const char *o);
int count(Triplestore *ts);

/* dictionnary functions*/

Dictionary *dictionary_create(size_t capacity);

uint32_t dictionary_get_id(
    Dictionary *dict,
    const char *string);

const char *dictionary_get_string(
    Dictionary *dict,
    uint32_t id);

void dictionary_free(
    Dictionary *dict);
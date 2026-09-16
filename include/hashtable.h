#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdint.h>
#include <stddef.h>

#define HASH_TABLE_SIZE 100

typedef struct Entry
{
    char *key;
    uint32_t value;
    struct Entry *next;
} Entry;

typedef struct
{
    Entry *buckets[HASH_TABLE_SIZE];
} HashTable;

HashTable *hashtable_create(void);

Entry *hashtable_find(
    HashTable *table,
    const char *key);

int hashtable_insert(
    HashTable *table,
    char *key,
    uint32_t value);

void hashtable_free(
    HashTable *table);

#endif

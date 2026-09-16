#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

static size_t hash_key(const char *key)
{
    size_t hash = 5381;

    while (*key != '\0')
    {
        hash = ((hash << 5) + hash) + (unsigned char)*key;
        key++;
    }

    return hash % HASH_TABLE_SIZE;
}

HashTable *hashtable_create(void)
{
    return calloc(1, sizeof(HashTable));
}

Entry *hashtable_find(
    HashTable *table,
    const char *key)
{
    Entry *current = table->buckets[hash_key(key)];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

int hashtable_insert(
    HashTable *table,
    char *key,
    uint32_t value)
{
    size_t index = hash_key(key);
    Entry *entry = malloc(sizeof(Entry));

    if (entry == NULL)
    {
        return 0;
    }

    entry->key = key;
    entry->value = value;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;

    return 1;
}

void hashtable_free(HashTable *table)
{
    if (table == NULL)
    {
        return;
    }

    for (size_t i = 0; i < HASH_TABLE_SIZE; i++)
    {
        Entry *current = table->buckets[i];

        while (current != NULL)
        {
            Entry *next = current->next;
            free(current);
            current = next;
        }
    }

    free(table);
}

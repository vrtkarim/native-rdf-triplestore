#include "triplestore.h"
#define dictionary
#include <stdlib.h>
#include <string.h>

static unsigned int hash_string(
    const char *string)
{
    unsigned int hash = 0;

    while (*string)
    {
        hash = hash * 31 + *string;
        string++;
    }

    return hash % 100;
}

static Entry *hashtable_find(
    HashTable *table,
    const char *key)
{
    unsigned int index =
        hash_string(key);

    Entry *current =
        table->buckets[index];

    return current;
}

static void hashtable_insert(
    HashTable *table,
    char *key,
    uint32_t value)
{
    unsigned int index =
        hash_string(key);

    Entry *entry =
        malloc(sizeof(Entry));

    if (entry == NULL)
    {
        return;
    }

    entry->key = key;
    entry->value = value;

    entry =
        table->buckets[index];

    table->buckets[index] =
        entry;
}

static HashTable *hashtable_create(void)
{
    HashTable *table =
        malloc(sizeof(HashTable));

    if (table == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 100; i++)
    {
        table->buckets[i] = NULL;
    }

    return table;
}

Dictionary *dictionary_create(
    size_t capacity)
{
    Dictionary *dict =
        malloc(sizeof(Dictionary));

    if (dict == NULL)
    {
        return NULL;
    }
    dict->hashtable =
        hashtable_create();

    if (dict->hashtable == NULL)
    {
        free(dict);
        return NULL;
    }
    dict->id_to_string =
        malloc(
            capacity * sizeof(char *));

    if (dict->id_to_string == NULL)
    {
        free(dict->hashtable);
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < capacity; i++)
    {
        dict->id_to_string[i] = NULL;
    }

    dict->size = 0;

    dict->capacity = capacity;

    return dict;
}

uint32_t dictionary_get_id(
    Dictionary *dict,
    const char *string)
{

    Entry *entry =
        hashtable_find(
            dict->hashtable,
            string);

    if (entry != NULL)
    {
        return entry->value;
    }

    if (dict->size >= dict->capacity)
    {
        return 0;
    }

    uint32_t new_id =
        dict->size + 1;

    char *copy =
        malloc(strlen(string) + 1);

    if (copy == NULL)
    {
        return 0;
    }

    strcpy(copy, string);
    dict->id_to_string[new_id] =
        copy;
    hashtable_insert(
        dict->hashtable,
        copy,
        new_id);
    dict->size++;

    return new_id;
}

const char *dictionary_get_string(
    Dictionary *dict,
    uint32_t id)
{
    if (id == 0)
    {
        return NULL;
    }

    if (id > dict->size)
    {
        return NULL;
    }

    return dict->id_to_string[id];
}

void dictionary_free(
    Dictionary *dict)
{
    if (dict == NULL)
    {
        return;
    }

    /*
     * Free strings.
     */
    for (size_t i = 1; i <= dict->size; i++)
    {
        free(dict->id_to_string[i]);
    }

    /*
     * Free hash table entries.
     */
    for (int i = 0; i < 100; i++)
    {
        Entry *current =
            dict->hashtable->buckets[i];
    }

    free(dict->id_to_string);

    free(dict->hashtable);

    free(dict);
}
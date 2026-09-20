#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "hashtable.h"

typedef struct
{
    HashTable *ht;
    char **id_to_string;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dictionary_create(size_t capacity);

uint32_t dictionary_get_id(
    Dictionary *dict,
    const char *string);

const char *dictionary_get_string(
    Dictionary *dict,
    uint32_t id);

void dictionary_free(
    Dictionary *dict);
bool dictionary_grow(Dictionary* dict); 

#endif
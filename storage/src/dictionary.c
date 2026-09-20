#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
Dictionary *dictionary_create(
    size_t capacity)
{
    Dictionary *dict =
        malloc(sizeof(Dictionary));

    if (dict == NULL)
    {
        return NULL;
    }
    dict->ht =
        hashtable_create();

    if (dict->ht == NULL)
    {
        free(dict);
        return NULL;
    }
    dict->id_to_string =
        malloc(
            (capacity + 1) * sizeof(char *));

    if (dict->id_to_string == NULL)
    {
        free(dict->ht);
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i <= capacity; i++)
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
            dict->ht,
            string);

    if (entry != NULL)
    {
        return entry->value;
    }

    if (dict->size >= dict->capacity)
    {
        if (dictionary_grow(dict) == false)
        {
            return 0;
        }
    }

    uint32_t new_id =
        dict->size + 1;

    if(string ==NULL){
        return 0;
    }
    char *copy =
        malloc(strlen(string) + 1);

    if (copy == NULL)
    {
        return 0;
    }

    strcpy(copy, string);
    if (!hashtable_insert(
            dict->ht,
            copy,
            new_id))
    {
        free(copy);
        return 0;
    }
    dict->id_to_string[new_id] = copy;
    dict->size++;

    return new_id;
}

const char *dictionary_get_string(
    Dictionary *dict,
    uint32_t id)
{
    if (dict == NULL || id == 0 || id > dict->size)
    {
        return NULL;
    }

    return dict->id_to_string[id];
}
bool dictionary_grow(Dictionary *dict)
{
    size_t newcapacity = dict->capacity * 2;
    char **new = realloc(dict->id_to_string,( newcapacity+1)*sizeof(char *));
    if (new == NULL)
    {
        printf("realloc failed...");
        return false;
    }
    for (size_t i = dict->capacity + 1; i <= newcapacity; i++)
    {
        new[i] = NULL;
    }
    dict->id_to_string = new;
    dict->capacity = newcapacity;
    return true;
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

    free(dict->id_to_string);

    hashtable_free(dict->ht);

    free(dict);
}
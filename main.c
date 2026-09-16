#include "./include/triplestore.h"
#include <stdio.h>



int main(void)
{
    Dictionary *dict =
        dictionary_create(10);


    uint32_t alice =
        dictionary_get_id(
            dict,
            "alice"
        );

    uint32_t knows =
        dictionary_get_id(
            dict,
            "knows"
        );

    uint32_t bob =
        dictionary_get_id(
            dict,
            "bob"
        );


    printf("alice ID = %u\n", alice);
    printf("knows ID = %u\n", knows);
    printf("bob ID = %u\n", bob);


    printf(
        "ID 1 = %s\n",
        dictionary_get_string(dict, 1)
    );

    printf(
        "ID 2 = %s\n",
        dictionary_get_string(dict, 2)
    );

    printf(
        "ID 3 = %s\n",
        dictionary_get_string(dict, 3)
    );


    /*
     * Ask for alice again.
     *
     * It should return 1,
     * NOT create a new ID.
     */
    uint32_t alice_again =
        dictionary_get_id(
            dict,
            "alice"
        );

    printf(
        "alice again = %u\n",
        alice_again
    );


    printf(
        "size = %zu\n",
        dict->size
    );

    printf(
        "capacity = %zu\n",
        dict->capacity
    );


    dictionary_free(dict);

    return 0;
}
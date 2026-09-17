#include "./include/triplestore.h"

#include <stdio.h>

int main(void)
{
    Triplestore *ts = create();

    if (ts == NULL)
    {
        printf("Could not create triplestore.\n");
        return 1;
    }

    insert(ts, "alice", "knows", "bob");
    insert(ts, "bob", "knows", "carol");
    insert(ts, "alice", "likes", "music");
    insert(ts, "alice", "knows", "bosssb");
    insert(ts, "bob", "kndows", "carcol");
    insert(ts, "alwice", "likdes", "mudsic");
    insert(ts, "alice", "knodws", "bodb");
    insert(ts, "bodb", "kndows", "cadrol");
    insert(ts, "aldsdice", "liskes", "musddic");
    insert(ts, "alisce", "knowews", "boddb");
    insert(ts, "bosb", "kdnows", "carodl");
    insert(ts, "alisce", "likdes", "music");
    insert(ts, "alicse", "kncows", "bob");
    insert(ts, "bobsdf", "knowcs", "carol");
    insert(ts, "alice", "likcces", "music");
    insert(ts, "alice", "knocws", "bob");
    insert(ts, "bob", "knowsc", "carol");
    insert(ts, "alisdfce", "likces", "musicc");

    printf("Number of triples: %d\n", count(ts));

    for (size_t i = 0; i < ts->size; i++)
    {
        Triple triple = ts->triples[i];

        printf(
            "(%u, %u, %u) = (%s, %s, %s)\n",
            triple.subject,
            triple.predicate,
            triple.object,
            dictionary_get_string(ts->dictionary, triple.subject),
            dictionary_get_string(ts->dictionary, triple.predicate),
            dictionary_get_string(ts->dictionary, triple.object));
        printf("dictioanary capacity, size are: %u, %u ",ts->dictionary->capacity, ts->dictionary->size);
    }

    triplestore_free(ts);

    return 0;
}
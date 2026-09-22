#include "triplestore.h"
#include "engine.h"
#include "fetcher.h"
#include "token.h"

int main(void)
{
    /* int n;
    TripleChars *t = fetch_TripleChars("full.ttl", &n);
    if (!t)
    {
        printf("data didnt load");
        return 0;
    }
    Triplestore *ts = create();

    for (int i = 0; i < n; i++)

        insert(ts, t[i].s, t[i].p, t[i].o);

    if (ts == NULL)
    {
        printf("Could not create triplestore.\n");
        return 1;
    }

    printf("Number of triples: %d\n", count(ts));

    char predicate[] = "http://xmlns.com/foaf/0.1/knows";
    Results *results = getTriples(
        ts,
        NULL,
        predicate,
        NULL,
        true,
        false,
        true);

    if (results != NULL)
    {
        printf("Triples with predicate %s:\n", predicate);

        for (size_t i = 0; i < results->size; i++)
        {
            Triple triple = results->triples[i];

            printf(
                "(%s, %s, %s)\n",
                dictionary_get_string(ts->dictionary, triple.subject),
                dictionary_get_string(ts->dictionary, triple.predicate),
                dictionary_get_string(ts->dictionary, triple.object));
        }

        free_results(results);
    } */

    /*for (size_t i = 0; i < ts->size; i++)
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
    }*/

    /* triplestore_free(ts);
    fetch_free(t, n); */

    char *query = "SELECT ?person ?friend WHERE { ?person < http: // xmlns.com/foaf/0.1/knows> ?friend .}";
    parseQuery(query);
    return 0;
}

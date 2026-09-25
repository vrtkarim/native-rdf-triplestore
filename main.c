#include "triplestore.h"
#include "engine.h"
#include "fetcher.h"
#include "token.h"
#include "executor.h"
#include <stdio.h>

int main(void)
{
    int n;
    TripleChars *t = fetch_TripleChars("full.ttl", &n);
    if (!t)
    {
        printf("data didnt load");
        return 1;
    }

    Triplestore *ts = create();

    if (ts == NULL)
    {
        fetch_free(t, n);
        printf("Could not create triplestore.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        insert(ts, t[i].s, t[i].p, t[i].o);
    }

    printf("Number of triples: %d\n", count(ts));

    char *query =
        "SELECT ?person ?friend WHERE { "
        "?person <http://xmlns.com/foaf/0.1/knows> ?friend . }";
    Results *results = execute(ts, query);

    if (results != NULL)
    {
        printf("Query results:\n");

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
    }

    triplestore_free(ts);
    fetch_free(t, n);
   

        return 0;
}

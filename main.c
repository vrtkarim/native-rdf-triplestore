#include "triplestore.h"
#include "engine.h"
#include "fetcher.h"
#include "token.h"
#include "parse.h"
#include <stdio.h>

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

    char *query = "SELECT ?person ?friend WHERE { ?person <http://xmlns.com/foaf/0.1/knows> ?friend . }";
    Tokens *tokens = parseQuery(query);

    if (tokens != NULL)
    {
        printf("number of tokens is %zu\n", tokens->size);

        for (size_t i = 0; i < tokens->size; i++)
        {
            printf(
                "token %zu: type=%d, text=%s\n",
                i,
                tokens->arrOfTokens[i].type,
                tokens->arrOfTokens[i].text);

        ParsedQuery *parsed_query = parseQuery(tokens);

        if (parsed_query != NULL)
        {
            printf(
                "parsed query type: %d\n"
                "subject: %s (variable=%s)\n"
                "predicate: %s (variable=%s)\n"
                "object: %s (variable=%s)\n",
                parsed_query->type,
                parsed_query->triplePattern.subject,
                parsed_query->triplePattern.sv ? "true" : "false",
                parsed_query->triplePattern.predicate,
                parsed_query->triplePattern.pv ? "true" : "false",
                parsed_query->triplePattern.object,
                parsed_query->triplePattern.ov ? "true" : "false");

            for (size_t i = 0; i < parsed_query->variables.count; i++)
            {
                printf(
                    "variable: %s, position: %d\n",
                    parsed_query->variables.vs[i].value,
                    parsed_query->variables.vs[i].position);
            }
        }
        }
    }

    return 0;
}

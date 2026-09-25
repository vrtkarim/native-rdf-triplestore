#include <executor.h>
Results *execute(Triplestore *ts, char *query)
{

    Tokens *tokens = getTokens(query);
    ParsedQuery *parsedQuery = parseQuery(tokens);
    Variables variables = parsedQuery->variables;

    Results *results = getTriples(ts, parsedQuery->triplePattern.subject,
                                  parsedQuery->triplePattern.predicate, parsedQuery->triplePattern.object, parsedQuery->triplePattern.sv, parsedQuery->triplePattern.pv, parsedQuery->triplePattern.ov);

    Triple *triples = results->triples;
    bool s = false;
    bool p = false;
    bool o = false;
    char *subject = NULL;
    char *predicate = NULL;
    char *object = NULL;
    for (size_t i = 0; i < variables.count; i++)
    {
        if (variables.vs[i].position == POSITION_SUBJECT)
        {
            subject = variables.vs[i].value;
            s = true;
        }
        if (variables.vs[i].position == POSITION_PREDICATE)
        {
            predicate = variables.vs[i].value;
            p = true;
        }
        if (variables.vs[i].position == POSITION_OBJECT)
        {
            object = variables.vs[i].value;
            o = true;
        }
    }
    if (s == true && p == false && o == false)
    {
        printf("%-45s\n", subject);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].subject));
        }
    }
    if (s == false && p == true && o == false)
    {
        printf("%-45s\n", predicate);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].predicate));
        }
    }
    if (s == false && p == false && o == true)
    {
        printf("%-45s\n", object);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].object));
        }
    }
    if (s == true && p == true && o == false)
    {
        printf("%-45s %-45s\n", subject, predicate);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s %-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].subject),
                dictionary_get_string(ts->dictionary, triples[i].predicate));
        }
    }
    if (s == true && p == false && o == true)
    {
        printf("%-45s %-45s\n", subject, object);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s %-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].subject),
                dictionary_get_string(ts->dictionary, triples[i].object));
        }
    }
    if (s == false && p == true && o == true)
    {
        printf("%-45s %-45s\n", predicate, object);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s %-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].predicate),
                dictionary_get_string(ts->dictionary, triples[i].object));
        }
    }
    if (s == true && p == true && o == true)
    {
        printf("%-45s %-45s %-45s\n", subject, predicate, object);
        for (size_t i = 0; i < results->size; i++)
        {
            printf(
                "%-45s %-45s %-45s\n",
                dictionary_get_string(ts->dictionary, triples[i].subject),
                dictionary_get_string(ts->dictionary, triples[i].predicate),
                dictionary_get_string(ts->dictionary, triples[i].object));
        }
    }

    return results;
}
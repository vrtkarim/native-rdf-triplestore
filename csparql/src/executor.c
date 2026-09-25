#include <executor.h>
Results *execute(Triplestore *ts, char *query)
{

    Tokens *tokens = getTokens(query);
    ParsedQuery *parsedQuery = parseQuery(tokens);

    Results *results = getTriples(ts, parsedQuery->triplePattern.subject,
                                  parsedQuery->triplePattern.predicate, parsedQuery->triplePattern.object, parsedQuery->triplePattern.sv, parsedQuery->triplePattern.pv, parsedQuery->triplePattern.ov);
    return results;
};
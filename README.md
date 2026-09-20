# Native RDF Triplestore

A small RDF triplestore written in C. RDF data is stored as subject,
predicate, and object triples. Strings are assigned numeric IDs so the
triplestore can compare and store values efficiently.

## Architecture

```text
main.c
	|
	+-- storage/   RDF data loading and in-memory storage
	|
	+-- engine/    Triple-pattern matching and query results
	|
	+-- csparql/   Planned SPARQL lexer and parser
```

### Storage

The `storage` module owns the RDF data model and its in-memory structures:

- `triplestore.c`: creates the triplestore, inserts triples, counts triples,
  and releases triplestore memory.
- `dictionary.c`: maps RDF strings to numeric IDs and maps IDs back to strings.
- `hashtable.c`: stores and finds dictionary entries.
- `fetcher.c`: loads triples from Turtle files using Raptor2.

Headers are in `storage/include` and implementations are in `storage/src`.

### Engine

The `engine` module searches the stored triples. It accepts a triple pattern
where each of subject, predicate, and object can be fixed or variable. It
returns matching triples in a dynamically allocated `Results` structure.

Headers are in `engine/include` and the implementation is in `engine/src`.

### CSparql: next implementation

The `csparql` module is reserved for the query language layer. It will be
implemented after the storage and engine layers are stable.

Planned stages:

1. Build a lexer that converts SPARQL text into tokens.
2. Build a parser that converts tokens into a query structure.
3. Support a small initial grammar with `SELECT`, `WHERE`, variables, IRIs,
   braces, and triple-pattern dots.
4. Convert parsed triple patterns into calls to the engine.
5. Print results for the variables selected by the query.

Example target query:

```sparql
SELECT ?person ?friend
WHERE {
		?person <http://xmlns.com/foaf/0.1/knows> ?friend .
}
```

## Building

The project uses GCC, Raptor2, and C17. From the repository root, build with:

```text
gcc -g -I engine/include -I storage/include \
		-I C:/msys64/ucrt64/include \
		-I C:/msys64/ucrt64/include/raptor2 \
		main.c storage/src/dictionary.c storage/src/hashtable.c \
		storage/src/fetcher.c storage/src/triplestore.c engine/src/engine.c \
		-L C:/msys64/ucrt64/lib -lraptor2 -o triplestore.exe
```

The same source files and include paths are configured in `.vscode/tasks.json`.

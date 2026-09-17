# Native RDF Triplestore

## Description

This is a small RDF triplestore written in C. It stores data as subject, predicate, and object triples. Strings are kept in a dictionary, and triples use IDs instead of storing the same strings repeatedly.

## Goals

The main goal is to turn this into a simple RDF database that can:

- Load data from Turtle (`.ttl`) files.
- Understand prefixes and convert them into full URIs.
- Store and load RDF data from files.
- Support literals and blank nodes.
- Find data using simple SPARQL queries.
- Make searching faster with indexes.

- Test loading, storing, and querying RDF data.

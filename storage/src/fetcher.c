#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raptor2/raptor.h>

#include "fetcher.h"



static void *xrealloc(void *ptr, size_t n)
{
    void *p = realloc(ptr, n);
    if (!p) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return p;
}

static char *xstrdup(const char *src)
{
    size_t n = strlen(src) + 1;
    char *copy = xrealloc(NULL, n);
    memcpy(copy, src, n);
    return copy;
}

/* strip "<uri>" / "\"lit\"" decoration from raptor_term_to_string output */
static void strip_decor(char *s)
{
    size_t n = strlen(s);

    if (s[0] == '<' && n >= 2 && s[n - 1] == '>') {
        memmove(s, s + 1, n - 2);
        s[n - 2] = '\0';
    } else if (s[0] == '"') {
        char *close = strrchr(s, '"');
        if (close && close != s) {
            size_t keep = (size_t)(close - s) - 1;
            memmove(s, s + 1, keep);
            s[keep] = '\0';
        }
    }
}

typedef struct {
    TripleChars *data;
    size_t len, cap;
    int errors;
} Fetch;

static void on_TripleChars(void *user_data, raptor_statement *st)
{
    Fetch *f = user_data;

    char *s = (char *)raptor_term_to_string(st->subject);
    char *p = (char *)raptor_term_to_string(st->predicate);
    char *o = (char *)raptor_term_to_string(st->object);

    if (!s || !p || !o) {
        f->errors = 1;
    } else {
        strip_decor(s);
        strip_decor(p);
        strip_decor(o);

        if (f->len == f->cap) {
            f->cap = f->cap ? f->cap * 2 : 16;
            f->data = xrealloc(f->data, f->cap * sizeof *f->data);
        }
        f->data[f->len].s = xstrdup(s); /* copy; raptor buffer freed below */
        f->data[f->len].p = xstrdup(p);
        f->data[f->len].o = xstrdup(o);
        f->len++;
    }

    raptor_free_memory(s);
    raptor_free_memory(p);
    raptor_free_memory(o);
}

/* raptor reports parse errors here; parse_file can still return 0 */
static void on_error(void *user_data, raptor_log_message *msg)
{
    Fetch *f = user_data;
    if (msg->level == RAPTOR_LOG_LEVEL_ERROR)
        f->errors = 1;
}

TripleChars *fetch_TripleChars(const char *path, int *count)
{
    Fetch f = {NULL, 0, 0, 0};

    *count = 0;

    FILE *probe = fopen(path, "r");
    if (!probe) {
        fprintf(stderr, "fetch: cannot open %s\n", path);
        return NULL;
    }
    fclose(probe);

    raptor_world *world = raptor_new_world();
    if (!world)
        return NULL;

    raptor_parser *parser = raptor_new_parser(world, "turtle");
    if (!parser) {
        raptor_free_world(world);
        return NULL;
    }

    raptor_parser_set_statement_handler(parser, &f, on_TripleChars);
    raptor_world_set_log_handler(world, &f, on_error);

    unsigned char *uri_str = raptor_uri_filename_to_uri_string(path);
    raptor_uri *base = raptor_new_uri(world, uri_str);

    int rc = raptor_parser_parse_file(parser, base, NULL);

    raptor_free_uri(base);
    raptor_free_memory(uri_str);
    raptor_free_parser(parser);
    raptor_free_world(world);

    if (rc != 0 || f.errors) {
        fprintf(stderr, "fetch: parse failed for %s\n", path);
        fetch_free(f.data, (int)f.len);
        return NULL;
    }

    *count = (int)f.len;
    return f.data;
}

void fetch_free(TripleChars *TripleCharss, int count)
{
    if (!TripleCharss)
        return;
    for (int i = 0; i < count; i++) {
        free((void *)TripleCharss[i].s);
        free((void *)TripleCharss[i].p);
        free((void *)TripleCharss[i].o);
    }
    free(TripleCharss);
}
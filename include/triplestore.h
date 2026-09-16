
typedef struct Triplestore Triplestore;

Triplestore *create(void);
void         free(Triplestore *ts);

void insert(Triplestore *ts, const char *s, const char *p, const char *o);


typedef struct { const char *s, *p, *o; } Triple;
int  ts_match(Triplestore *ts, const char *s, const char *p, const char *o,
              Triple *out, int max_out);

int  count(Triplestore *ts);
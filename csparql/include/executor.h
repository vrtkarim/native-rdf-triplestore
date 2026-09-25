#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "engine.h"
#include "parse.h"
#include "triplestore.h"

Results *execute(Triplestore *ts, char *query);

#endif
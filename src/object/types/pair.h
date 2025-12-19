#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Pair {
    struct Object obj;
    struct Object* first;
    struct Object* rest;
};

struct Etor_rec;
struct OutStream;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Pair* pair_new(struct Object* first, struct Object* rest);
struct Pair* pair_new_empty(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void pair_showWith(struct Pair* pair, const string_t open, const string_t close, struct OutStream* outStream);

/* Object functions ******************/

struct Object* pair_close_rec(struct Pair* pair, struct Etor_rec* etor);
count_t pair_count(struct Pair* pair);
bool_t pair_match(struct Pair* pair, struct Pair* other, struct Vector* bindings);
bool_t pair_eval_rec(struct Pair* pair, struct Etor_rec* etor, struct Object** value);
void pair_show(struct Pair* pair, struct OutStream* outStream);

#include <stdio.h>

#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Pair {
    struct Object obj;
    struct Object* first;
    struct Object* rest;
};

struct Etor_Rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Pair* pair_new(struct Object* first, struct Object* rest);
struct Pair* pair_new_empty(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t pair_close_rec(struct Pair* pair, struct Etor_Rec* etor, struct Object** value);
count_t pair_count(struct Pair* pair);
bool_t pair_eval_rec(struct Pair* pair, struct Etor_Rec* etor, struct Object** value);
void pair_show(struct Pair* pair, FILE* stream);

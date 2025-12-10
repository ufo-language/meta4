#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Sequence {
    struct Object obj;
    count_t nExprs;
    struct Object* exprs[];
};

struct Etor_rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Sequence* sequence_new(count_t nExprs, struct Object* exprs[]);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* sequence_close_rec(struct Sequence* seq, struct Etor_rec* etor);
bool_t sequence_eval_rec(struct Sequence* seq, struct Etor_rec* etor, struct Object** value);
void sequence_show(struct Sequence* seq, FILE* stream);

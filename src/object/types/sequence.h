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

struct Evaluator;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Sequence* sequence_new(count_t nExprs, struct Object* exprs[]);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t sequence_eval(struct Sequence* sequence, struct Evaluator* etor, struct Object** value);
void sequence_show(struct Sequence* sequence, FILE* stream);

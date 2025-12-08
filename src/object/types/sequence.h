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

struct Etor_Rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Sequence* sequence_new(count_t nExprs, struct Object* exprs[]);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t sequence_close_rec(struct Sequence* sequence, struct Etor_Rec* etor, struct Object** value);
bool_t sequence_eval_rec(struct Sequence* sequence, struct Etor_Rec* etor, struct Object** value);
void sequence_show(struct Sequence* sequence, FILE* stream);

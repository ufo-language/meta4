#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct IntVar {
    struct Object obj;
    int_t i;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntVar* intVar_new(int_t i);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t intVar_equal(struct IntVar* intVar, struct IntVar* other);
void intVar_show(struct IntVar* intVar, FILE* stream);

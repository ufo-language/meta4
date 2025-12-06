#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_recursive.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Integer {
    struct Object obj;
    int_t i;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Integer* integer_new(int_t i);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t integer_equal(struct Integer* integer, struct Integer* other);
void integer_show(struct Integer* integer, FILE* stream);

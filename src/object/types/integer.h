#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Integer {
    struct Object obj;
    int_t i;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Integer* integer_new(int_t i);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void integer_show(struct Integer* integer, struct OutStream* outStream);

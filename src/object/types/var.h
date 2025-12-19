#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Var {
    struct Object obj;
    struct Object* value;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Var* var_new(struct Object* value);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void var_show(struct Var* var, FILE* stream);

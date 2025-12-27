#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Variable {
    struct Object obj;
    struct Object* value;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Variable* variable_new(struct Object* value);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void variable_show(struct Variable* var, struct OutStream* outStream);

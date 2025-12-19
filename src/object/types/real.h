#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Real {
    struct Object obj;
    real_t r;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Real* real_new(real_t i);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t real_equal(struct Real* real, struct Real* other);
void real_show(struct Real* real, struct OutStream* outStream);

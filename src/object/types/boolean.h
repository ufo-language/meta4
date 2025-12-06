#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Boolean {
    struct Object obj;
    bool_t b;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Boolean* boolean_new(bool_t b);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void boolean_show(struct Boolean* boolean, FILE* stream);

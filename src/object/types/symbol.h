#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Symbol {
    #include "object/types/symbolic_fields.h"
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbol* symbol_new(const string_t name);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

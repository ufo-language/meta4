#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* symbol_new(const string_t name);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void symbol_show(struct Symbolic* symbol, FILE* stream);

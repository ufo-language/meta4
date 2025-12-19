#pragma once

#include <stdio.h>

#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void show(struct Object* obj, struct OutStream* outStream);

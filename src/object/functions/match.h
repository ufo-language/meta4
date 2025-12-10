#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t match(struct Object* obj, struct Object* other, struct Vector* bindings);
bool_t matchObjs(count_t nObjs, struct Object* objs[], struct Object* other[], struct Vector* bindings);

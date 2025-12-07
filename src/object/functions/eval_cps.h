#pragma once

#include "object/typeids.h"

struct Etor_CPS;
struct Object;

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void eval_cps(struct Object* obj, struct Etor_CPS* etor);

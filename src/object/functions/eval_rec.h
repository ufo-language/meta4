#pragma once

#include "object/typeids.h"

enum EvaluationType;
struct Etor_rec;
struct Object;

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t eval_rec(struct Object* obj, struct Etor_rec* etor, struct Object** value);

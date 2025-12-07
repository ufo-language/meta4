#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Etor_Rec;
struct Object;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t close(struct Object* obj, struct Etor_Rec* etor, struct Object** value);

/* Private functions *********************************************************/

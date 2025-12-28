#pragma once

#include <stdio.h>

#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum CompareResult {
    CompareResult_Less = -1,
    CompareResult_Equal = 0,
    CompareResult_Greater = 1,
    CompareResult_Unordered = 2
};

struct Object;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Returns false if the two objects are not equal.
   The result variable contains -1, 0, or +1.
*/
enum CompareResult compare(struct Object* obj, struct Object* other);

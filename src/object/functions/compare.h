#pragma once

#include <stdio.h>

#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum CompareResult {
    CompareLess = -1,
    CompareEqual = 0,
    CompareGreater = 1,
    CompareUnordered = 2
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

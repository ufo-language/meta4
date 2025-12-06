#include "_typedefs.h"

#include "object/object.h"
#include "object/types/intarray.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct IntVector {
    struct Object obj;
    count_t top;
    struct IntArray* elems;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

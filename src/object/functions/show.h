#include <stdio.h>

#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

typedef void (*ShowFunction)(struct Object* obj, FILE* stream);

struct ShowFunction_handler {
    enum TypeID typeId;
    ShowFunction function;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

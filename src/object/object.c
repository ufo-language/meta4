#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/object.h"
#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Object* object_new(enum TypeId typeId, count_t nWords) {
    struct Object* obj = memory_alloc(nWords);
    #if 0
    fprintf(stderr, "object_new %-10s : %2lu words @ %p\n", typeName(typeId), nWords, obj);
    #endif
    obj->typeId = typeId;
    obj->nWords = nWords;
    return obj;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

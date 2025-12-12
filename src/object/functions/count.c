#include "_typedefs.h"

#include "object/typeids.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/pair.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t count(struct Object* obj, int_t* nElems) {
    switch(obj->typeId) {
        case OT_Array:
            *nElems = ((struct Array*)obj)->nElems;
            return true;
        case OT_ByteBuffer:
            break;
        case OT_HashTable:
            break;
        case OT_IntArray:
            break;
        case OT_IntVector:
            break;
        case OT_Pair:
            *nElems = pair_count((struct Pair*)obj);
            return true;
        case OT_String:
            break;
        case OT_Term:
            *nElems = 1 + ((struct Term*)obj)->nArgs;
            return true;
        case OT_Vector:
            *nElems = ((struct Vector*)obj)->top;
            return true;
        default:
            return false;
    }
    fprintf(stderr, "count: Unhandled type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

/* Private functions *********************************************************/

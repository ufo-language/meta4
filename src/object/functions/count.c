#include "_typedefs.h"

#include "object/typeids.h"
#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t count(struct Object* obj, int_t* count) {
    switch(obj->typeId) {
        case OT_Array:         break;
        case OT_ByteBuffer:    break;
        case OT_HashTable:     break;
        case OT_IntArray:      break;
        case OT_IntVector:     break;
        case OT_List:          break;
        case OT_String:        break;
        case OT_Vector:        break;
        default:
            return false;
    }
    fprintf(stderr, "show: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

/* Private functions *********************************************************/

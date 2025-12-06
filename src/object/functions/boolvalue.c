#include "_typedefs.h"

#include "object/typeids.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/boolean.h"
#include "object/types/ifthen.h"
#include "object/types/integer.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t boolValue(struct Object* obj) {
    switch(obj->typeId) {
        case OT_Apply:         break;
        case OT_Array:         return ((struct Array*)obj)->nElems != 0;
        case OT_BinOp:         break;
        case OT_Boolean:       return ((struct Boolean*)obj)->b;
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: break;
        case OT_Dec:           break;
        case OT_Device:        break;
        case OT_Evaluator:     break;
        case OT_Function:      break;
        case OT_HashTable:     break;
        case OT_Identifier:    break;
        case OT_IfThen:        break;
        case OT_Inc:           break;
        case OT_IntArray:      break;
        case OT_Integer:       return ((struct Integer*)obj)->i != 0;
        case OT_IntVector:      break;
        case OT_IVar:          break;
        case OT_Let:           break;
        case OT_List:          break;
        case OT_Nil:           return false;
        case OT_Null:          break;
        case OT_Primitive:     break;
        case OT_Quote:         break;
        case OT_Real:          break;
        case OT_Sequence:      break;
        case OT_Vector:         break;
        case OT_String:        break;
        case OT_Symbol:        break;
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_While:         break;
        default:
            fprintf(stderr, "show: Unknown type ID %u\n", obj->typeId);
            return false;
    }
    return true;
}
/* Private functions *********************************************************/

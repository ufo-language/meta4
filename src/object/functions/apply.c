#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/boolean.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t apply(struct Object* obj, struct Etor_rec* etorRec, count_t nArgs, struct Object* args[]) {
#if 0
    switch(obj->typeId) {
        case OT_Apply:         return true;
        case OT_Array:         return ((struct Array*)obj)->nElems != 0;
        case OT_BinOp:         return true;
        case OT_Boolean:       return ((struct Boolean*)obj)->b;
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: break;
        case OT_Dec:           return true;
        case OT_Device:        return true;
        case OT_Etor_Rec:      return true;
        case OT_Function:      return true;
        case OT_HashTable:     break;
        case OT_Identifier:    return true;
        case OT_IfThen:        return true;
        case OT_Inc:           return true;
        case OT_IntArray:      break;
        case OT_Integer:       return ((struct Integer*)obj)->i != 0;
        case OT_IntVector:     break;
        case OT_IntVar:        return ((struct IntVar*)obj)->i != 0;
        case OT_Let:           return true;
        case OT_Pair:          break;
        case OT_Nil:           return false;
        case OT_Null:          break;
        case OT_Primitive:     return true;
        case OT_Quote:         return true;
        case OT_Real:          break;
        case OT_Sequence:      return true;
        case OT_String:        return ((struct String*)obj)->nChars > 0;
        case OT_Symbol:        return true;
        case OT_Test:          return true;
        case OT_User:          return true;
        case OT_Var:           return true;
        case OT_Vector:        break;
        case OT_While:         return true;
        default:
            break;
    }
#endif
    fprintf(stderr, "boolValue: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

/* Private functions *********************************************************/

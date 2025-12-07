#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/equal.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t equal(struct Object* obj, struct Object* other) {
    /* Special cases */
    if (obj->typeId == OT_Integer) {
        switch (other->typeId) {
            case OT_IntVar: return ((struct Integer*)obj)->i == ((struct IntVar*)other)->i;
            case OT_Integer: return ((struct Integer*)obj)->i == ((struct Integer*)other)->i;
            default: return false;
        }
    }
    if (obj->typeId == OT_IntVar) {
        switch (other->typeId) {
            case OT_Integer: return ((struct IntVar*)obj)->i == ((struct Integer*)other)->i;
            case OT_IntVar: return ((struct IntVar*)obj)->i == ((struct IntVar*)other)->i;
            default: return false;
        }
    }
    /* If types are not equal then objects can't be equal */
    if (obj->typeId != other->typeId) {
        return false;
    }
    switch(obj->typeId) {
        case OT_Apply:         break;
        case OT_Array:         break; /*return array_equal((struct Array*)obj, (struct Array*)(other));*/
        case OT_BinOp:         break;
        case OT_Boolean:       break; /*return boolean_equal((struct Boolean*)obj, stream);*/
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: break;
        case OT_Dec:           break;
        case OT_Device:        break;
        case OT_Etor_Rec:      break;
        case OT_Function:      break;
        case OT_HashTable:     break;
        case OT_Identifier:    return obj == other;
        case OT_IfThen:        break;
        case OT_Inc:           break;
        case OT_IntArray:      break; /*return intArray_equal((struct IntArray*)obj, stream);*/
        case OT_Integer:       break; /* already handled above */
        case OT_IntVector:     break; /*return intVector_equal((struct IntVector*)obj, stream);*/
        case OT_IntVar:        break; /* already handled above */
        case OT_Let:           break;
        case OT_Pair:          break;
        case OT_Nil:           return true;
        case OT_Null:          break;
        case OT_Primitive:     break;
        case OT_Quote:         break;
        case OT_Real:          break;
        case OT_Sequence:      break; /*return sequence_equal((struct Sequence*)obj, stream);*/
        case OT_String:        return string_equal((struct String*)obj, (struct String*)other);
        case OT_Symbol:        break;
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_Vector:        break; /*return vector_equal((struct Vector*)obj, stream);*/
        case OT_While:         break;
        default:
            break;
    }
    fprintf(stderr, "equal: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    fputs("UNKNOWN", stderr);
    return false;
}

/* Private functions *********************************************************/

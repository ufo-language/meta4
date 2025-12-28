#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/compare.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/string.h"
#include "object/types/symbol.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

static enum CompareResult _compareInts(int_t i1, int_t i2) {
    if (i1 < i2) return CompareResult_Less;
    if (i1 > i2) return CompareResult_Greater;
    return CompareResult_Equal;
}

enum CompareResult compare(struct Object* obj, struct Object* other) {
    /* Special cases */
    if (obj->typeId == OT_Integer) {
        switch (other->typeId) {
            case OT_IntVar: return _compareInts(((struct Integer*)obj)->i, ((struct IntVar*)other)->i);
            case OT_Integer: return _compareInts(((struct Integer*)obj)->i, ((struct Integer*)other)->i);
            default: return CompareResult_Unordered;
        }
    }
    if (obj->typeId == OT_IntVar) {
        switch (other->typeId) {
            case OT_IntVar: return _compareInts(((struct IntVar*)obj)->i, ((struct IntVar*)other)->i);
            case OT_Integer: return _compareInts(((struct IntVar*)obj)->i, ((struct Integer*)other)->i);
            default: return CompareResult_Unordered;
        }
    }
    /* If types are not equal then objects can't be compared */
    if (obj->typeId != other->typeId) {
        return CompareResult_Unordered;
    }
    switch(obj->typeId) {
        case OT_Application:   break;
        case OT_Array:         return array_compare((struct Array*)obj, (struct Array*)other);
        case OT_BinOp:         break;
        case OT_Boolean:       break; /*return boolean_compare((struct Boolean*)obj, stream);*/
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: break;
        case OT_Dec:           break;
        case OT_Etor_Rec:      break;
        case OT_Function:      break;
        case OT_HashTable:     break;
        case OT_Identifier:    return identifier_compare((struct Identifier*)obj, (struct Identifier*)other);
        case OT_IfThen:        break;
        case OT_Inc:           break;
        case OT_IntArray:      break; /*return intArray_compare((struct IntArray*)obj, stream);*/
        case OT_Integer:       break; /* already handled above */
        case OT_IntVector:     break; /*return intVector_compare((struct IntVector*)obj, stream);*/
        case OT_IntVar:        break; /* already handled above */
        case OT_Let:           break;
        case OT_OutStream:     break;
        case OT_Pair:          break;
        case OT_Nil:           return CompareResult_Equal;
        case OT_Null:          break;
        case OT_Primitive:     break;
        case OT_Quote:         break;
        case OT_Real:          break;
        case OT_Sequence:      break; /*return sequence_compare((struct Sequence*)obj, stream);*/
        case OT_String:        return string_compare((struct String*)obj, (struct String*)other);
        case OT_Symbol:        return symbol_compare((struct Symbol*)obj, (struct Symbol*)other);
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_Vector:        break; /*return vector_compare((struct Vector*)obj, stream);*/
        case OT_While:         break;
        default:               break;
    }
    fprintf(stderr, "compare: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

/* Private functions *********************************************************/

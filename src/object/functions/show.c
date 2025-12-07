#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/boolean.h"
#include "object/types/identifier.h"
#include "object/types/intarray.h"
#include "object/types/integer.h"
#include "object/types/intvector.h"
#include "object/types/nil.h"
#include "object/types/sequence.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void show(struct Object* obj, FILE* stream) {
    switch(obj->typeId) {
        case OT_Apply:         break;
        case OT_Array:         array_show((struct Array*)obj, stream); return;
        case OT_BinOp:         break;
        case OT_Boolean:       boolean_show((struct Boolean*)obj, stream); return;
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: break;
        case OT_Dec:           break;
        case OT_Device:        break;
        case OT_Evaluator:     break;
        case OT_Function:      break;
        case OT_HashTable:     break;
        case OT_Identifier:    identifier_show((struct Symbolic*)obj, stream); return;
        case OT_IfThen:        break;
        case OT_Inc:           break;
        case OT_IntArray:      intArray_show((struct IntArray*)obj, stream); return;
        case OT_Integer:       integer_show((struct Integer*)obj, stream); return;
        case OT_IntVector:     intVector_show((struct IntVector*)obj, stream); return;
        case OT_IVar:          break;
        case OT_Let:           break;
        case OT_List:          break;
        case OT_Nil:           nil_show((struct Nil*)obj, stream); return;
        case OT_Null:          break;
        case OT_Primitive:     break;
        case OT_Quote:         break;
        case OT_Real:          break;
        case OT_Sequence:      sequence_show((struct Sequence*)obj, stream); return;
        case OT_String:        string_show((struct String*)obj, stream); return;
        case OT_Symbol:        symbol_show((struct Symbolic*)obj, stream); return;
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_Vector:        vector_show((struct Vector*)obj, stream); return;
        case OT_While:         break;
        default:
            break;
    }
    fprintf(stderr, "show: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    fputs("UNKNOWN", stream);
}

/* Private functions *********************************************************/

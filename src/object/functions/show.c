#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/show.h"
#include "object/types/array.h"


/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Array;
struct Integer;
struct Nil;

/* Forward declarations ******************************************************/

void array_show  (struct Array*,   FILE* stream);
void integer_show(struct Integer*, FILE* stream);
void nil_show    (struct Nil*,     FILE* stream);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void show(struct Object* obj, FILE* stream) {
    switch(obj->typeId) {
        case OT_Apply:         break;
        case OT_Array:         array_show((struct Array*)obj, stream); return;
        case OT_BinOp:         break;
        case OT_Boolean:       break;
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
        case OT_Integer:       integer_show((struct Integer*)obj, stream); return;
        case OT_IVar:          break;
        case OT_Let:           break;
        case OT_List:          break;
        case OT_Nil:           nil_show((struct Nil*)obj, stream); return;
        case OT_Null:          break;
        case OT_Primitive:     break;
        case OT_Quote:         break;
        case OT_Real:          break;
        case OT_Sequence:      break;
        case OT_String:        break;
        case OT_Symbol:        break;
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_While:         break;
        default:
            fprintf(stderr, "show: Unknown type ID %u\n", obj->typeId);
            fputs("UNKNOWN", stream);
            break;
    }
}

/* Private functions *********************************************************/

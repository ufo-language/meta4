#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Array;
struct Evaluator;
struct Integer;
struct Nil;
struct Object;

/* Forward declarations ******************************************************/

bool_t array_eval  (struct Array*,   struct Evaluator*, struct Object**);
bool_t integer_eval(struct Integer*, struct Evaluator*, struct Object**);
bool_t nil_eval    (struct Nil*,     struct Evaluator*, struct Object**);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t eval(struct Object* obj, struct Evaluator* etor, struct Object** value) {
    switch(obj->typeId) {
        case OT_Apply:         break;
        case OT_Array:         return array_eval((struct Array*)obj, etor, value);
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
        case OT_Integer:       return integer_eval((struct Integer*)obj, etor, value);
        case OT_IVar:          break;
        case OT_Let:           break;
        case OT_List:          break;
        case OT_Nil:           return nil_eval((struct Nil*)obj, etor, value);
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
            fprintf(stderr, "eval: Unknown type ID %u\n", obj->typeId);
            return false;
    }
    return false;
}

/* Private functions *********************************************************/

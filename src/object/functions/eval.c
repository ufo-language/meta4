#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Array;
struct Evaluator;
struct IfThen;
struct Object;
struct Sequence;

/* Forward declarations ******************************************************/

bool_t array_eval   (struct Array*,    struct Evaluator*, struct Object**);
bool_t ifThen_eval  (struct IfThen*,   struct Evaluator*, struct Object**);
bool_t sequence_eval(struct Sequence*, struct Evaluator*, struct Object**);

bool_t _const_eval  (struct Object*,   struct Evaluator*, struct Object**);
bool_t _evalError   (struct Object*,   struct Evaluator*, struct Object**);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t eval(struct Object* obj, struct Evaluator* etor, struct Object** value) {
    switch(obj->typeId) {
        case OT_Apply:         break;
        case OT_Array:         return array_eval((struct Array*)obj, etor, value);
        case OT_BinOp:         break;
        case OT_Boolean:       return _const_eval(obj, etor, value);
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: return _evalError(obj, etor, value);
        case OT_Dec:           break;
        case OT_Device:        return _const_eval(obj, etor, value);;
        case OT_Evaluator:     break;
        case OT_Function:      break;
        case OT_HashTable:     break;
        case OT_Identifier:    break;
        case OT_IfThen:        return ifThen_eval((struct IfThen*)obj, etor, value);
        case OT_Inc:           break;
        case OT_IntArray:      break;
        case OT_Integer:       return _const_eval(obj, etor, value);
        case OT_IntVector:      break;
        case OT_IVar:          break;
        case OT_Let:           break;
        case OT_List:          break;
        case OT_Nil:           return _const_eval(obj, etor, value);
        case OT_Null:          return _evalError(obj, etor, value);
        case OT_Primitive:     return _const_eval(obj, etor, value);;
        case OT_Quote:         break;
        case OT_Real:          return _const_eval(obj, etor, value);;
        case OT_Sequence:      return sequence_eval((struct Sequence*)obj, etor, value);
        case OT_Vector:         break;
        case OT_String:        return _const_eval(obj, etor, value);;
        case OT_Symbol:        return _const_eval(obj, etor, value);;
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

bool_t _const_eval(struct Object* obj, struct Evaluator* etor, struct Object** value) {
    *value = obj;
    return true;
}

bool_t _evalError(struct Object* obj, struct Evaluator* etor, struct Object** value) {
    fprintf(stderr, "Error evaluating object of type '%s'\n", typeName(obj->typeId));
    return false;
}

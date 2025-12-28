#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/compare.h"
#include "object/functions/match.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/function.h"
#include "object/types/integer.h"
#include "object/types/pair.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

#include "debug.h"
bool_t match(struct Object* obj, struct Object* other, struct Vector* bindings) {
    if (obj == other) {
        return true;
    }
    if (obj->typeId == OT_Identifier) {
        vector_bindPair(bindings, obj, other);
        return true;
    }
    if (obj->typeId != other->typeId) {
        return false;
    }
    if (obj->typeId < OT_ConstantLimit) {
        return compare(obj, other) == CompareResult_Equal;
    }
    switch (obj->typeId) {
        /* Non-constants */
        case OT_Array: return array_match((struct Array*)obj, (struct Array*)other, bindings);
        case OT_Pair:  return pair_match((struct Pair*)obj, (struct Pair*)other, bindings);
#if 0
        case OT_Application:      break;
        case OT_Array:      return array_eval_rec((struct Array*)obj, etor, value);
        case OT_BinOp:      break;
        case OT_ByteBuffer: break;
        case OT_Dec:        return dec_eval_rec((struct Dec*)obj, etor, value);
        case OT_Etor_Rec:   break;
        case OT_Function:   break;
        case OT_HashTable:  break;
        case OT_Identifier: return identifier_eval_rec((struct Identifier*)obj, etor, value);
        case OT_IfThen:     return ifThen_eval_rec((struct IfThen*)obj, etor, value);
        case OT_Inc:        break;
        case OT_IntArray:   break;
        case OT_IntVector:  break;
        case OT_Let:        break;
        case OT_Pair:       return pair_eval_rec((struct Pair*)obj, etor, value);
        case OT_Quote:      break;
        case OT_Sequence:   return sequence_eval_rec((struct Sequence*)obj, etor, value);
        case OT_Test:       break;
        case OT_User:       break;
        case OT_Var:        break;
        case OT_Vector:     break;
        case OT_While:      break;
        /* Non-datatypes */
        case OT_ConstantLimit:
        case OT_Null:
            fprintf(stderr, "Error evaluating object of type '%s'\n", typeName(obj->typeId));
            return false;
#endif
        default:
            break;
    }
    fprintf(stderr, "match: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

bool_t matchObjs(count_t nObjs, struct Object* objs[], struct Object* other[], struct Vector* bindings) {
    index_t savedTop = vector_top(bindings);
    for (index_t n=0; n<nObjs; ++n) {
        if (!match(objs[n], other[n], bindings)) {
            vector_setTop(bindings, savedTop);
            return false;
        }
    }
    return true;
}

/* Private functions *********************************************************/

#include <stdio.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/dec.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/pair.h"
#include "object/types/sequence.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t eval_rec(struct Object* obj, struct Etor_rec* etor, struct Object** value) {
    switch(obj->typeId) {
        /* Constants */
        case OT_Boolean:
        case OT_Device:
        case OT_Integer:
        case OT_IntVar:
        case OT_Nil:
        case OT_Primitive:
        case OT_Real:
        case OT_String:
        case OT_Symbol:
            *value = obj;
            return true;

        /* Non-constants */
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

        default:
            break;
    }
    fprintf(stderr, "eval_rec: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

/* Private functions *********************************************************/

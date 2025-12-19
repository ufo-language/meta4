#include <stdio.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/application.h"
#include "object/types/array.h"
#include "object/types/dec.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/inc.h"
#include "object/types/let.h"
#include "object/types/pair.h"
#include "object/types/quote.h"
#include "object/types/sequence.h"
#include "object/types/term.h"
#include "object/types/while.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t eval_rec(struct Object* obj, struct Etor_rec* etor, struct Object** value) {
    index_t savedEnv = etor_rec_envSave(etor);
    switch(obj->typeId) {
        /* Constants, or at least treated like constants */
        case OT_Boolean:
        case OT_Etor_Rec:
        case OT_Integer:
        case OT_IntVar:
        case OT_Nil:
        case OT_OutStream:
        case OT_Primitive:
        case OT_Real:
        case OT_String:
        case OT_Symbol:
            *value = obj;
            return true;

        /* Non-constants */
        case OT_Application: return application_eval((struct Application*)obj, etor, value);
        case OT_Array:       return array_eval_rec((struct Array*)obj, etor, value);
        case OT_BinOp:       break;
        case OT_ByteBuffer:  break;
        case OT_Dec:         return dec_eval_rec((struct Dec*)obj, etor, value);
        case OT_Function:    return function_eval_rec((struct Function*)obj, etor, value);;
        case OT_HashTable:   break;
        case OT_Identifier:  return identifier_eval_rec((struct Identifier*)obj, etor, value);
        case OT_IfThen:      return ifThen_eval_rec((struct IfThen*)obj, etor, value);
        case OT_Inc:         return inc_eval_rec((struct Inc*)obj, etor, value);
        case OT_IntArray:    break;
        case OT_IntVector:   break;
        case OT_Let:         return let_eval_rec((struct Let*)obj, etor, value);
        case OT_Pair:        return pair_eval_rec((struct Pair*)obj, etor, value);
        case OT_Quote:       return quote_eval_rec((struct Quote*)obj, etor, value);
        case OT_Sequence:    return sequence_eval_rec((struct Sequence*)obj, etor, value);
        case OT_Term:        return term_eval_rec((struct Term*)obj, etor, value);
        case OT_Test:        break;
        case OT_User:        break;
        case OT_Var:         break;
        case OT_Vector:      break;
        case OT_While:       return while_eval_rec((struct While*)obj, etor, value);

        /* Non-datatypes; should never get here */
        case OT_ConstantLimit:
        case OT_Null:
            fprintf(stderr, "Error evaluating object of type '%s'\n", typeName(obj->typeId));
            return false;

        default:
            break;
    }
    etor_rec_envRestore(etor, savedEnv);
    fprintf(stderr, "eval_rec: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return false;
}

/* Private functions *********************************************************/

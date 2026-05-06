#include <stdio.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/application.h"
#include "object/types/array.h"
#include "object/types/binding.h"
#include "object/types/binop.h"
#include "object/types/dec.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/inc.h"
#include "object/types/let.h"
#include "object/types/pair.h"
#include "object/types/quote.h"
#include "object/types/sequence.h"
#include "object/types/subscript.h"
#include "object/types/term.h"
#include "object/types/trycatchfinally.h"
#include "object/types/while.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

struct Object* close_rec(struct Object* obj, struct Etor_rec* etor) {
    switch(obj->typeId) {
        /* Constants */
        case OT_Boolean:
        case OT_Integer:
        case OT_IntVar:
        case OT_Nil:
        case OT_OutStream:
        case OT_Primitive:
        case OT_Real:
        case OT_String:
        case OT_Symbol:
            return obj;

        /* Non-evaluated types (return as-is) */
        case OT_ByteBuffer:
        case OT_Etor_Rec:
        case OT_HashTable:
        case OT_IntArray:
        case OT_IntVector:
        case OT_Test:
        case OT_User:
        case OT_Var:
        case OT_Vector:
            return obj;

        /* Types evaluated recursively (close recursively) */
        case OT_Application:     return application_close((struct Application*)obj, etor);
        case OT_Array:           return array_close_rec((struct Array*)obj, etor);
        case OT_Binding:         return binding_close_rec((struct Binding*)obj, etor);
        case OT_BinOp:           return binOp_close_rec((struct BinOp*)obj, etor);
        case OT_Dec:             return dec_close_rec((struct Dec*)obj, etor);
        case OT_Function:        return function_close_rec((struct Function*)obj, etor);
        case OT_Identifier:      return identifier_close_rec((struct Identifier*)obj, etor);
        case OT_IfThen:          return ifThen_close_rec((struct IfThen*)obj, etor);
        case OT_Inc:             return inc_close_rec((struct Inc*)obj, etor);
        case OT_Let:             return let_close_rec((struct Let*)obj, etor);
        case OT_Pair:            return pair_close_rec((struct Pair*)obj, etor);
        case OT_Quote:           return quote_close_rec((struct Quote*)obj, etor);
        case OT_Sequence:        return sequence_close_rec((struct Sequence*)obj, etor);
        case OT_Subscript:       return subscript_close_rec((struct Subscript*)obj, etor);
        case OT_Term:            return term_close_rec((struct Term*)obj, etor);
        case OT_TryCatchFinally: return tryCatchFinally_close_rec((struct TryCatchFinally*)obj, etor);
        case OT_While:           return while_close_rec((struct While*)obj, etor);

        /* Non-datatypes */
        case OT_ConstantLimit:
        case OT_Null:
            fprintf(stderr, "Error closing object of type '%s'\n", typeName(obj->typeId));
            return obj;

        default:
            break;
    }
    fprintf(stderr, "close_rec: Unhandled type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return obj;
}

/* Private functions *********************************************************/

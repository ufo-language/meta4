#include <stdio.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/application.h"
#include "object/types/array.h"
#include "object/types/dec.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/let.h"
#include "object/types/pair.h"
#include "object/types/sequence.h"
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
        case OT_Dec:
        case OT_Device:
        case OT_Integer:
        case OT_IntVar:
        case OT_Nil:
        case OT_Primitive:
        case OT_Real:
        case OT_String:
        case OT_Symbol:
            return obj;

        /* Non-constants */
        case OT_Application: return application_close((struct Application*)obj, etor);
        case OT_Array:       return array_close_rec((struct Array*)obj, etor);
        case OT_BinOp:       break;
        case OT_ByteBuffer:  break;
        /* case OT_Dec:        return dec_close_rec((struct Dec*)obj, etor); */
        case OT_Etor_Rec:    break;
        case OT_Function:    break;
        case OT_HashTable:   break;
        case OT_Identifier:  return identifier_close_rec((struct Identifier*)obj, etor);
        case OT_IfThen:      return ifThen_close_rec((struct IfThen*)obj, etor);
        case OT_Inc:         break;
        case OT_IntArray:    break;
        case OT_IntVector:   break;
        case OT_Let:         return let_close_rec((struct Let*)obj, etor);
        case OT_Pair:        return pair_close_rec((struct Pair*)obj, etor);
        case OT_Quote:       break;
        case OT_Sequence:    return sequence_close_rec((struct Sequence*)obj, etor);
        case OT_Test:        break;
        case OT_User:        break;
        case OT_Var:         break;
        case OT_Vector:      break;
        case OT_While:       return while_close_rec((struct While*)obj, etor);

        /* Non-datatypes */
        case OT_ConstantLimit:
        case OT_Null:
            fprintf(stderr, "Error closing object of type '%s'\n", typeName(obj->typeId));
            return obj;

        default:
            break;
    }
    fprintf(stderr, "close_rec: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return obj;
}

/* Private functions *********************************************************/

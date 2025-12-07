#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "object/evaluator/etor_cps.h"
#include "object/functions/eval_cps.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/sequence.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void _const_eval_cps(struct Object*, struct Etor_CPS*);
void _evalError_cps(struct Object*, struct Etor_CPS*);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void eval_cps(struct Object* obj, struct Etor_CPS* etor) {
    switch(obj->typeId) {
        /* Constants */
        case OT_Boolean:
        case OT_Device:
        case OT_Etor_Rec:
        case OT_Integer:
        case OT_Nil:
        case OT_Primitive:
        case OT_Real:
        case OT_String:
        case OT_Symbol:
            vector_push(etor->vStack, obj);
            return;

        /* Non-constants */
        case OT_Apply:
            break;
        case OT_Array:
            //array_eval_cps((struct Array*)obj, etor); return;
            break;
        case OT_BinOp:
            break;
        case OT_ByteBuffer:
            break;
        case OT_Dec:
            break;
        case OT_Function:
            break;
        case OT_HashTable:
            break;
        case OT_Identifier:
            //identifier_eval_cps((struct Symbolic*)obj, etor); return;
            break;
        case OT_IfThen:
            return;
        case OT_Inc:
            break;
        case OT_IntArray:
            break;
        case OT_IntVector:
            break;
        case OT_IVar:
            break;
        case OT_Let:
            break;
        case OT_List:
            break;
        case OT_Quote:
            break;
        case OT_Sequence:
            //sequence_eval_cps((struct Sequence*)obj, etor); return;
            break;
        case OT_Test:
            break;
        case OT_User:
            break;
        case OT_Var:
            break;
        case OT_Vector:
            break;
        case OT_While:
            break;

        /* Non-data types */
        case OT_ConstantLimit:
        case OT_Null:
            fprintf(stderr, "Error evaluating object of type '%s'\n", typeName(obj->typeId));
            assert(false);
            exit(1);
            return;

        default:
            break;
    };
    fprintf(stderr, "eval_cps: Unhandled type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    return;
}

/* Private functions *********************************************************/

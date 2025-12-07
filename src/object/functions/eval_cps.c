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
        case OT_Apply:         break;
        case OT_Array:         //array_eval_cps((struct Array*)obj, etor); return;
        case OT_BinOp:         break;
        case OT_Boolean:       _const_eval_cps(obj, etor); return;
        case OT_ByteBuffer:    break;
        case OT_ConstantLimit: _evalError_cps(obj, etor); return;
        case OT_Dec:           break;
        case OT_Device:        _const_eval_cps(obj, etor); return;
        case OT_Etor_Rec:     break;
        case OT_Function:      break;
        case OT_HashTable:     break;
        case OT_Identifier:    //return identifier_eval_cps((struct Symbolic*)obj, etor);
        case OT_IfThen:        ifThen_eval_cps((struct IfThen*)obj, etor); return;
        case OT_Inc:           break;
        case OT_IntArray:      break;
        case OT_Integer:       _const_eval_cps(obj, etor); return;
        case OT_IntVector:     break;
        case OT_IVar:          break;
        case OT_Let:           break;
        case OT_List:          break;
        case OT_Nil:           _const_eval_cps(obj, etor); return;
        case OT_Null:          _evalError_cps(obj, etor); return;
        case OT_Primitive:     _const_eval_cps(obj, etor); return;
        case OT_Quote:         break;
        case OT_Real:          _const_eval_cps(obj, etor); return;
        case OT_Sequence:      //sequence_eval_cps((struct Sequence*)obj, etor); return;
        case OT_String:        _const_eval_cps(obj, etor); return;
        case OT_Symbol:        _const_eval_cps(obj, etor); return;
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_Vector:        break;
        case OT_While:         break;
        default:
            fprintf(stderr, "eval_cps: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
            return;
    };
}

/* Private functions *********************************************************/

void _const_eval_cps(struct Object* obj, struct Etor_CPS* etor) {
    etor_cps_vPush(etor, obj);
}

void _evalError_cps(struct Object* obj, struct Etor_CPS* etor) {
    fprintf(stderr, "Error evaluating object of type '%s'\n", typeName(obj->typeId));
    assert(false);
    exit(1);
}

#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/freevars.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/dec.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/pair.h"
#include "object/types/sequence.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void freeVars(struct Object* obj, struct Vector* freeVars_) {
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
            return;

        /* Non-constants */
        case OT_Application:
            break;
        case OT_Array: {
                struct Array* array = (struct Array*)obj;
                for (index_t n=0; n<array->nElems; ++n) {
                    freeVars(array->elems[n], freeVars_);
                }
            }
            return;
        case OT_BinOp:
            break;
        case OT_ByteBuffer:
            break;
        case OT_Dec:
            /* return dec_eval_rec((struct Dec*)obj, etor, value); */
            break;
        case OT_Etor_Rec:
            break;
        case OT_Function:
            break;
        case OT_HashTable:
            break;
        case OT_Identifier:
            vector_push(freeVars_, obj);
            return;
        case OT_IfThen: {
                struct IfThen* ifThen = (struct IfThen*)obj;
                freeVars(ifThen->cond, freeVars_);
                freeVars(ifThen->conseq, freeVars_);
                freeVars(ifThen->alt, freeVars_);
            }
            return;
        case OT_Inc:
            break;
        case OT_IntArray:
            break;
        case OT_IntVector:
            break;
        case OT_Let:
            break;
        case OT_Pair: {
                if (obj == (struct Object*)g_emptyPair) {
                    return;
                }
                struct Pair* pair = (struct Pair*)obj;
                freeVars(pair->first, freeVars_);
                freeVars(pair->rest, freeVars_);
            }
            return;
        case OT_Quote:
            break;
        case OT_Sequence: {
                struct Sequence* seq = (struct Sequence*)obj;
                for (index_t n=0; n<seq->nExprs; ++n) {
                    freeVars(seq->exprs[n], freeVars_);
                }
            }
            return;
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

        /* Non-datatypes */
        case OT_ConstantLimit:
        case OT_Null:
            fprintf(stderr, "Error getting free variables from object of type '%s'\n", typeName(obj->typeId));
            return;

        default:
            break;
    }
    fprintf(stderr, "eval_rec: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
}

/* Private functions *********************************************************/

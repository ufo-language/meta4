#include <assert.h>

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/primitives/defineprims.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/subscript.h"
#include "object/types/variable.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void prim_binOp_defineAll(struct Vector* env);

static bool_t _assign(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
// static bool_t _plus(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void prim_binOp_defineAll(struct Vector* env) {
    defineMacro(env, ":=", _assign, 2, OT_Any, OT_Any);
    // definePrim(env, "+", _plus, 2, OT_Any, OT_Any);
}

static bool_t _assign(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    struct Object* lhs = args[0];
    struct Object* rhs = args[1];
    struct Object* rhsVal;
    if (!eval_rec(rhs, etor, &rhsVal)) {
        *value = rhsVal;
        return false;
    }
    switch (lhs->typeId) {
        case OT_Identifier:
            *value = rhsVal;
            return identifier_assign((struct Identifier*)lhs, rhsVal, etor);
        case OT_Subscript: {
                struct Object* base;
                struct Object* index;
                struct Object* error;
                struct Subscript* subs = (struct Subscript*)lhs;
                if (!subscript_evalParts(subs->base, subs->index, etor, &base, &index, &error)) {
                    *value = error;
                    return false;
                }
                switch (subscript_assign(base, index, rhsVal)) {
                    case SubscriptResult_OK:
                        *value = rhsVal;
                        return true;
                    case SubscriptResult_IndexOutOfBounds:
                        *value = (struct Object*)errorTerm1("SubscriptError", "Subscript out of bounds", index);
                        return false;
                    case SubscriptResult_IndexType:
                        *value = (struct Object*)errorTerm_objAndType("SubscriptError", "Object not usable as index", index);
                        return false;
                    case SubscriptResult_KeyNotFound:
                        *value = (struct Object*)errorTerm_objAndType("SubscriptError", "Key not found in collection", index);
                        return false;
                    case SubscriptResult_UnhashableKey:
                        *value = (struct Object*)errorTerm_objAndType("SubscriptError", "Unhashable key", index);
                        return false;
                    case SubscriptResult_ObjectNotSubscriptable:
                        *value = (struct Object*)errorTerm_objAndType("SubscriptError", "Object is not subscriptable", base);
                        return false;
                    default:
                        assert(false);
                        return false;
                }
            }
        case OT_Var:
            ((struct Variable*)lhs)->value = rhsVal;
            *value = rhsVal;
            return true;
        case OT_IntVar:
            if (rhsVal->typeId != OT_Integer) {
                *value = (struct Object*)errorTerm_objAndType("IntVarError", "Assigned value is not an an integer", rhsVal);
                return false;
            }
            ((struct IntVar*)lhs)->i = ((struct Integer*)rhsVal)->i;
            *value = rhsVal;
            return true;
        default:
            *value = (struct Object*)errorTerm_objAndType("AssignError", "Unable to assign to LHS", lhs);
            return false;

    }
}

#if 0
static bool_t _plus(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    // count_t nElems;
    // if (!count(args[0], &nElems)) {
    //     return false;
    // }
    // *value = (struct Object*)integer_new((int_t)nElems);
    return true;
}
#endif

/* Private functions *********************************************************/

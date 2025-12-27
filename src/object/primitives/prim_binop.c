#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/primitives/defineprims.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/subscript.h"
#include "object/types/variable.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void prim_binOp_defineAll(struct Vector* env);

static bool_t _assign(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _plus(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void prim_binOp_defineAll(struct Vector* env) {
    defineMacro(env, ":=", _assign, 2, OT_Any, OT_Any);
    definePrim(env, "+", _plus, 2, OT_Any, OT_Any);
}

#include "debug.h"
static bool_t _assign(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    struct Object* lhs = args[0];
    struct Object* rhs = args[1];
    struct Object* rhsVal;
    if (!eval_rec(rhs, etor, &rhsVal)) {
        return false;
    }
    switch (lhs->typeId) {
        case OT_Identifier:
            *value = rhsVal;
            return identifier_assign((struct Identifier*)lhs, rhsVal, etor);
        case OT_Subscript: {
                struct Object* error;
                if (subscript_assign((struct Subscript*)lhs, rhsVal, &error)) {
                    *value = rhsVal;
                    return false;
                }
                *value = error;
                return false;
            }
#if 0
        case OT_Var:
            return var_assign((struct Variable*)lhs, rhsVal);
        case OT_IntVar:
            if (rhsVal->typeId != OT_Integer) {
                *value = (struct Object*)errorTerm1("IntArray", "Assigned value is not an an integer", rhsVal);
                return false;
            }
            return intVar_assign((struct IntVar*)lhs, ((struct Integer*)rhsVal)->i);
#endif
        default:
            *value = (struct Object*)errorTerm1("Assign", "Unable to assign to LHS", lhs);
            return false;

    }
}

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

/* Private functions *********************************************************/

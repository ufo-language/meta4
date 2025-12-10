#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/match.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/let.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Let* let_new(struct Object* lhs, struct Object* rhs) {
    struct Let* let = (struct Let*)object_new(OT_Let, NWORDS(*let));
    let->lhs = lhs;
    let->rhs = rhs;
    return let;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

struct Object* let_close_rec(struct Let* let, struct Etor_rec* etor) {
    struct Object* closedRhs = close_rec(let->rhs, etor);
    return (struct Object*)let_new(let->lhs, closedRhs);
}

bool_t let_eval_rec(struct Let* let, struct Etor_rec* etor, struct Object** value) {
    struct Object* rhsVal;
    if (!eval_rec(let->rhs, etor, &rhsVal)) {
        *value = rhsVal;
        return false;
    }
    if (!match(let->lhs, rhsVal, etor->env)) {
        fputs("ERROR: Let match bind error, lhs = ", stderr);
        show(let->lhs, stderr);
        fputs(", rhs = ", stderr);
        show(rhsVal, stderr);
        fputc('\n', stderr);
        return false;
    }
    *value = (struct Object*)g_nil;
    return true;
}

void let_show(struct Let* let, FILE* stream) {
    fputs("let ", stream);
    show(let->lhs, stream);
    fputs(" = ", stream);
    show(let->rhs, stream);
}

/* Private functions *********************************************************/

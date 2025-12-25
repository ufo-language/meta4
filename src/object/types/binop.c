#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_cps.h"
#include "object/types/application.h"
#include "object/types/binop.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct BinOp* binOp_new(struct Object* lhs, struct Object* oper, struct Object* rhs) {
    struct BinOp* binOp = (struct BinOp*)object_new(OT_BinOp, NWORDS(struct BinOp));
    binOp->lhs = lhs;
    binOp->oper = oper;
    binOp->rhs = rhs;
    struct Object* args[] = {lhs, rhs};
    binOp->application = application_new(oper, 2, args);
    return binOp;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* binOp_close_rec(struct BinOp* binOp, struct Etor_rec* etor) {
    struct Object* closedLhs = close_rec(binOp->lhs, etor);
    struct Object* closedOper = close_rec(binOp->oper, etor);
    struct Object* closedRhs = close_rec(binOp->rhs, etor);
    struct Object* closedArgs[] = {closedLhs, closedRhs};
    binOp->application = application_new(closedOper, 2, closedArgs);
    return (struct Object*)binOp;
}

bool_t binOp_eval_rec(struct BinOp* binOp, struct Etor_rec* etor, struct Object** value) {
    return application_eval_rec(binOp->application, etor, value);
}

void binOp_show(struct BinOp* binOp, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'O', binOp->lhs,
        'C', ' ',
        'O', binOp->oper,
        'C', ' ',
        'O', binOp->rhs,
        0);
}

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/functions/eval_rec.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/application.h"
#include "object/types/function.h"
#include "object/types/trycatchfinally.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/*
struct TryCatchFinally {
    struct Object obj;
    struct Object* tryExpr;
    struct Function* catchRules;
    struct Object* finallyExpr;
};
*/
#include <assert.h>
struct TryCatchFinally* tryCatchFinally_new(struct Object* tryExpr, struct Function* catchRules, struct Object* finallyExpr) {
    struct TryCatchFinally* tcf = (struct TryCatchFinally*)object_new(OT_TryCatchFinally, NWORDS(struct TryCatchFinally));
    tcf->tryExpr = tryExpr;
    tcf->catchRules = catchRules;
    tcf->finallyExpr = finallyExpr;
    struct Object* args[1] = {(struct Object*)g_nil};
    return tcf;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* tryCatchFinally_close_rec(struct TryCatchFinally* tcf, struct Etor_rec* etor) {
}

bool_t tryCatchFinally_eval_rec(struct TryCatchFinally* tcf, struct Etor_rec* etor, struct Object** value) {
    struct Object* tryValue;
    struct Object* catchValue;
    struct Object* finallyValue;
    bool_t trySuccess = false;
    bool_t catchSuccess = false;
    bool_t finallySuccess = false;
    trySuccess = eval_rec(tcf->tryExpr, etor, &tryValue);
    if (!trySuccess) {
        struct Object* args[1] = {tryValue};
        catchSuccess = function_apply(tcf->catchRules, etor, 1, args, &catchValue);
    }
    finallySuccess = eval_rec(tcf->finallyExpr, etor, &finallyValue);
    if (!finallySuccess) {
        *value = finallyValue;
        return false;
    }
    if (trySuccess) {
        *value = tryValue;
        return true;
    }
    if (catchSuccess) {
        *value = catchValue;
        return true;
    }
    /* Exception thrown and not caught */
    *value = tryValue;
    return false;
}

void tryCatchFinally_freeVars(struct TryCatchFinally* tcf, struct Vector* freeVars) {
}

void tryCatchFinally_show(struct TryCatchFinally* tcf, struct OutStream* outStream) {
}

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/types/function.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Function* function_new(struct Identifier* name, count_t nParams, struct Object* params[], struct Object* body, struct Function* nextRule) {
    struct Function* function = (struct Function*)object_new(OT_Function, NWORDS(*function) + nParams);
    function->name = name;
    function->nParams = nParams;
    memcpy(function->params, params, nParams * sizeof(struct Object*));
    function->body = body;
    function->closedBody = g_uniqueObject;
    function->nextRule = nextRule;
    return function;
}

struct Function* function_new_empty(void) {
    struct Function* function = (struct Function*)object_new(OT_Function, NWORDS(*function));
    function->name = g_idNil;
    function->nParams = 0;
    function->body = (struct Object*)g_nil;
    function->closedBody = g_uniqueObject;
    function->nextRule = function;
    return function;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t function_close_rec(struct Function* function, struct Etor_Rec* etor, struct Object** value) {
    while (function != g_emptyFunction) {
        // save env
        // prebind parameters
        // close body
        // save closed body in function->closedBody
        // restore env
    }
    *value = (struct Object*)function;
    return true;
}

bool_t function_eval_rec(struct Function* function, struct Etor_Rec* etor, struct Object** value) {
    return function_close_rec(function, etor, value);
}

void function_show(struct Function* function, FILE* stream) {

}

/* Private functions *********************************************************/

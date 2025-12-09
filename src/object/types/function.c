#include "_typedefs.h"

#include "memory/memory.h"
#include "object/types/function.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/freevars.h"
#include "object/functions/show.h"
#include "object/types/identifier.h"
#include "object/types/vector.h"
#include "object/functions/close_rec.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static bool_t _closeRule(struct FunctionRule* rule, struct Etor_rec* etor, struct FunctionRule** closedRule);
static void _showRule(struct FunctionRule* rule, FILE* stream);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Function* function_new(struct Identifier* name, count_t nParams, struct Object* params[], struct Object* body, struct FunctionRule* nextRule) {
    struct Function* function = (struct Function*)object_new(OT_Function, NWORDS(*function) + nParams);
    function->name = name;
    function->rules = g_emptyFunctionRule;
    function->closedRules = g_emptyFunctionRule;
    function_attachFinalRule(function, nParams, params, body);
    return function;
}

void function_attachFinalRule(struct Function* function, count_t nParams, struct Object* params[], struct Object* body) {
    struct FunctionRule** rule = &function->rules;
    while (*rule != g_emptyFunctionRule) {
        *rule = (*rule)->nextRule;
    }
    *rule = (struct FunctionRule*)memory_alloc(NWORDS(*rule));
    (*rule)->nParams = nParams;
    memcpy((*rule)->params, params, nParams * sizeof(struct Object*));
    (*rule)->body = body;
    (*rule)->closedBody = g_uniqueObject;
    (*rule)->nextRule = g_emptyFunctionRule;
}

struct FunctionRule* function_emptyRule(void) {
    struct FunctionRule* rule = (struct FunctionRule*)memory_alloc(NWORDS(*rule));
    rule->body = (struct Object*)g_nil;
    rule->closedBody = (struct Object*)g_nil;
    rule->nextRule = rule;
    rule->nParams = 0;
    return rule;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t function_close_rec(struct Function* function, struct Etor_rec* etor, struct Object** value) {
    fputs("function_close_rec function = ", stderr);
    function_show(function, stderr);
    fputc('\n', stderr);
    return _closeRule(function->rules, etor, &function->closedRules);
}

bool_t function_eval_rec(struct Function* function, struct Etor_rec* etor, struct Object** value) {
    return function_close_rec(function, etor, value);
}

void function_show(struct Function* function, FILE* stream) {
    fputs("fun ", stream);
    if (function->name != g_idNil) {
        identifier_show(function->name, stream);
    }
    bool_t firstIter;
    struct FunctionRule* rule;
    for (firstIter=true, rule=function->rules; rule!=g_emptyFunctionRule; firstIter=false, rule=rule->nextRule) {
        if (!firstIter) {
            fputs(" | ", stream);
        }
        _showRule(rule, stream);
    }
    fputs(" end", stream);
}

/* Private functions *********************************************************/

static bool_t _closeRule(struct FunctionRule* rule, struct Etor_rec* etor, struct FunctionRule** closedRule) {
    if (rule == g_emptyFunctionRule) {
        *closedRule = rule;
        return true;
    }
    fputs("_closeRule current rule = ", stderr);
    _showRule(rule, stderr);
    fputc('\n', stderr);

    /* Close current rule */
    struct FunctionRule* newRule = (struct FunctionRule*)memory_alloc(NWORDS(*rule));

    /* Save the current environment */
    index_t savedEnv = etor_rec_envSave(etor);
    /* Prebind each parameter to itself */
    for (index_t n=0; n<rule->nParams; n++) {
        struct Object* param = rule->params[n];
        struct Vector* freeVars_ = vector_new();
        fputs("_closeRule param = ", stderr);
        show(param, stderr);
        fputc('\n', stderr);
        freeVars(param, freeVars_);
        for (int m=0; m<freeVars_->top; m++) {
            struct Identifier* freeVar = (struct Identifier*)freeVars_->elems->elems[n];
            etor_rec_bind(etor, freeVar, (struct Object*)freeVar);
        }
    }
    /* Close the function body */
    struct Object* closedBody;
    if (!close_rec(rule->body, etor, &closedBody)) {
        return false;
    }
    rule->closedBody = closedBody;
    /* Restore the environment */
    etor_rec_envRestore(etor, savedEnv);

    /* Close next rule */
    if (!_closeRule(rule->nextRule, etor, &newRule->nextRule)) {
        return false;
    }
    return true;
}

static void _showRule(struct FunctionRule* rule, FILE* stream) {
    fputc('(', stream);
    array_showElemsWith(rule->nParams, rule->params, ", ", stream);
    fputs(") = ", stream);
    show(rule->body, stream);
}

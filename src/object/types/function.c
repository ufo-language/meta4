#include <assert.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/types/function.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/freevars.h"
#include "object/functions/match.h"
#include "object/functions/show.h"
#include "object/types/identifier.h"
#include "object/types/vector.h"
#include "object/functions/close_rec.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static bool_t _closeRule(struct FunctionRule* rule, struct Etor_rec* etor);
static void _showRule(struct FunctionRule* rule, FILE* stream);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Function* function_new(struct Identifier* name) {
    struct Function* function = (struct Function*)object_new(OT_Function, NWORDS(*function));
    function->name = name;
    function->rules = g_emptyFunctionRule;
    return function;
}

void function_attachFinalRule(struct Function* function, count_t nParams, struct Object* params[], struct Object* body) {
    /* Create the new rule */
    struct FunctionRule* newRule = (struct FunctionRule*)memory_alloc(NWORDS(struct FunctionRule) + nParams);
    newRule->nParams = nParams;
    memcpy(newRule->params, params, nParams * sizeof(struct Object*));
    newRule->body = body;
    newRule->closedBody = g_uniqueObject;
    newRule->nextRule = g_emptyFunctionRule;
    /* Attach it to the list of rules */
    struct FunctionRule* previousRule = g_emptyFunctionRule;
    struct FunctionRule* rule = function->rules;
    while (rule != g_emptyFunctionRule) {
        previousRule = rule;
        rule = rule->nextRule;
    }
    if (previousRule == g_emptyFunctionRule) {
        function->rules = newRule;
    }
    else {
        previousRule->nextRule = newRule;
    }
}

struct FunctionRule* function_emptyRule(void) {
    struct FunctionRule* rule = (struct FunctionRule*)memory_alloc(NWORDS(*rule));
    rule->body = (struct Object*)g_nil;
    rule->closedBody = g_uniqueObject;
    rule->nextRule = rule;
    rule->nParams = 0;
    return rule;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t function_apply(struct Function* function, struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    index_t savedEnv = etor_rec_envSave(etor);
    /* Check each rule for a match */
    struct FunctionRule* rule = function->rules;
    while (rule != g_emptyFunctionRule) {
        if (rule->nParams == nArgs) {
            if (matchObjs(nArgs, rule->params, args, etor->env)) {
                return eval_rec(rule->closedBody, etor, value);
            }
        }
        /* Restore the environment because matchObjs creates new bindings */
        etor_rec_envRestore(etor, savedEnv);
        rule = rule->nextRule;
    }
    return false;
}

bool_t function_close_rec(struct Function* function, struct Etor_rec* etor, struct Object** value) {
    index_t savedEnv = etor_rec_envSave(etor);
    for (struct FunctionRule* rule=function->rules; rule!=g_emptyFunctionRule; rule=rule->nextRule) {
        if (!_closeRule(rule, etor)) {
            etor_rec_envRestore(etor, savedEnv);
            return false;
        }
    }
    etor_rec_envRestore(etor, savedEnv);
    *value = (struct Object*)function;
    return true;
}

bool_t function_eval_rec(struct Function* function, struct Etor_rec* etor, struct Object** value) {
    return function_close_rec(function, etor, value);
}

void function_show(struct Function* function, FILE* stream) {
    fputs("fun ", stream);
    if (function->name != g_idNil) {
        identifier_show(function->name, stream);
    }
    assert(function->rules != g_emptyFunctionRule);
    struct FunctionRule* rule = function->rules;
    _showRule(rule, stream);
    for (rule = rule->nextRule; rule != g_emptyFunctionRule; rule = rule->nextRule) {
        fputs(" | ", stream);
        _showRule(rule, stream);
    }
    fputs(" end", stream);
}

/* Private functions *********************************************************/

static bool_t _closeRule(struct FunctionRule* rule, struct Etor_rec* etor) {
    if (rule == g_emptyFunctionRule) {
        return true;
    }
    /* Close current rule */
    /* Save the current environment */
    index_t savedEnv = etor_rec_envSave(etor);
    /* Prebind each parameter to itself */
    for (index_t n=0; n<rule->nParams; n++) {
        struct Object* param = rule->params[n];
        struct Vector* freeVars_ = vector_new();
        freeVars(param, freeVars_);
        for (int m=0; m<freeVars_->top; m++) {
            struct Identifier* freeVar = (struct Identifier*)freeVars_->elems->elems[m];
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
    if (!_closeRule(rule->nextRule, etor)) {
        return false;
    }
    return true;
}

static void _showRule(struct FunctionRule* rule, FILE* stream) {
    fputc('(', stream);
    array_showElems(rule->nParams, rule->params, ", ", stream);
    fputs(") = ", stream);
    show(rule->body, stream);
}

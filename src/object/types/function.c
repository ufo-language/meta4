#include <assert.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/freevars.h"
#include "object/functions/match.h"
#include "object/functions/show.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/outstream.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _function_closeRule(struct FunctionRule* rule, struct Etor_rec* etor);
static void _function_showRule(struct FunctionRule* rule, struct OutStream* outStream);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Function* function_new(struct Identifier* name) {
    struct Function* function = (struct Function*)object_new(OT_Function, NWORDS(*function));
    function->name = name;
    function->argEvalType = ArgEvalType_Function;
    function->rules = g_emptyFunctionRule;
    return function;
}

struct Function* function_newMacro(struct Identifier* name) {
    struct Function* function = function_new(name);
    function->argEvalType = ArgEvalType_Macro;
    return function;
}

void function_addlRule(struct Function* function, count_t nParams, struct Object* params[], struct Object* body) {
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

bool_t function_apply(struct Function* function, struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    index_t savedEnv = etor_rec_envSave(etor);
    /* Check each rule for a match */
    struct FunctionRule* rule = function->rules;
    while (rule != g_emptyFunctionRule) {
        if (rule->nParams == nArgs) {
            if (matchObjs(nArgs, rule->params, args, etor->env)) {
                bool_t success = eval_rec(rule->closedBody, etor, value);
                etor_rec_envRestore(etor, savedEnv);
                return success;
            }
        }
        /* Restore the environment because matchObjs creates new bindings */
        etor_rec_envRestore(etor, savedEnv);
        rule = rule->nextRule;
    }
    return false;
}

/* Object functions ******************/

struct Object* function_close_rec(struct Function* function, struct Etor_rec* etor) {
    for (struct FunctionRule* rule=function->rules; rule!=g_emptyFunctionRule; rule=rule->nextRule) {
        index_t savedEnv = etor_rec_envSave(etor);
        _function_closeRule(rule, etor);
        etor_rec_envRestore(etor, savedEnv);
    }
    return (struct Object*)function;
}

bool_t function_eval_rec(struct Function* function, struct Etor_rec* etor, struct Object** value) {
    *value = function_close_rec(function, etor);
    return true;
}

void function_show(struct Function* function, struct OutStream* outStream) {
    assert(outStream->streamType < 2);
    outStream_writeString(outStream, function->argEvalType == ArgEvalType_Function ? "fun " : "macro ");
    assert(outStream->streamType < 2);
    if (function->name != g_idNil) {
        symbolic_show((struct Symbolic*)function->name, outStream);
        assert(outStream->streamType < 2);
    }
    assert(function->rules != g_emptyFunctionRule);
    struct FunctionRule* rule = function->rules;
    assert(outStream->streamType < 2);
    _function_showRule(rule, outStream);
    assert(outStream->streamType < 2);
    for (rule = rule->nextRule; rule != g_emptyFunctionRule; rule = rule->nextRule) {
        assert(outStream->streamType < 2);
        outStream_writeString(outStream, " | ");
        assert(outStream->streamType < 2);
        _function_showRule(rule, outStream);
        assert(outStream->streamType < 2);
    }
    outStream_writeString(outStream, " end");
}

/* Private functions *********************************************************/

static void _function_closeRule(struct FunctionRule* rule, struct Etor_rec* etor) {
    if (rule == g_emptyFunctionRule) {
        return;
    }
    /* Close current rule */
    /* Save the current environment */
    index_t savedEnv = etor_rec_envSave(etor);
    /* Prebind each parameter to itself */
    for (index_t n=0; n<rule->nParams; ++n) {
        struct Object* param = rule->params[n];
        struct Vector* freeVars_ = vector_new();
        freeVars(param, freeVars_);
        for (index_t m=0; m<freeVars_->nElems; ++m) {
            struct Identifier* freeVar = (struct Identifier*)freeVars_->elems->elems[m];
            etor_rec_bind(etor, freeVar, (struct Object*)freeVar);
        }
    }
    /* Close the function body */
    rule->closedBody = close_rec(rule->body, etor);
    /* Restore the environment */
    etor_rec_envRestore(etor, savedEnv);
}

static void _function_showRule(struct FunctionRule* rule, struct OutStream* outStream) {
    assert(outStream->streamType < 2);
    array_show_usingElems(rule->nParams, rule->params, "(", ", ", ") = ", outStream);
    assert(outStream->streamType < 2);
    show(rule->body, outStream);
    assert(outStream->streamType < 2);
}

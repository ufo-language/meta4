#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
#include "object/types/array.h"
#include "object/types/identifier.h"
#include "object/types/primitive.h"
#include "utils.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static bool_t _checkArgs(struct Primitive* prim, count_t nArgs, struct Object* args[], PrimFunction* function);
static bool_t _emptyPrimFunction(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
#if 0
void _showRule(struct PrimitiveRule* rule);
#endif

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Primitive* prim_new(const string_t name, enum PrimType primType) {
    struct Primitive* prim = (struct Primitive*)object_new(OT_Primitive, NWORDS(*prim));
    prim->name = identifier_new(name);
    prim->rules = g_emptyPrimRule;
    prim->primType = primType;
    return prim;
}

struct Primitive* prim_newFunction(const string_t name) {
    return prim_new(name, PrimType_Function);
}

struct Primitive* prim_newMacro(const string_t name) {
    return prim_new(name, PrimType_Macro);
}

/* TODO use va_list here */
static struct PrimitiveRule* _newRule(count_t nParams, enum TypeId paramTypes[], PrimFunction function) {
    count_t nParamsToAllocate = nParams;
    if (nParams == COUNT_MAX) {
        nParamsToAllocate = 0;
    }
    struct PrimitiveRule* rule = (struct PrimitiveRule*)memory_alloc(NWORDS(*rule) + NBYTES_TO_WORDS(sizeof(enum TypeId) * nParamsToAllocate));
    rule->function = function;
    rule->nextRule = g_emptyPrimRule;
    rule->nParams = nParams;
    memcpy(rule->paramTypes, paramTypes, sizeof(enum TypeId) * nParamsToAllocate);
    return rule;
}

static struct PrimitiveRule* _vnewRule(PrimFunction function, count_t nParams, va_list paramTypes) {
    count_t nParamsToAllocate = nParams;
    if (nParams == COUNT_MAX) {
        nParamsToAllocate = 0;
    }
    struct PrimitiveRule* rule = (struct PrimitiveRule*)memory_alloc(NWORDS(*rule) + NBYTES_TO_WORDS(sizeof(enum TypeId) * nParamsToAllocate));
    rule->function = function;
    rule->nextRule = g_emptyPrimRule;
    rule->nParams = nParams;
    for (index_t n=0; n<nParamsToAllocate; n++) {
        rule->paramTypes[n] = va_arg(paramTypes, enum TypeId);
    }
    return rule;
}

void prim_addRule(struct Primitive* prim, count_t nParams, enum TypeId paramTypes[], PrimFunction function) {
    /* Create the new rule */
    struct PrimitiveRule* newRule = _newRule(nParams, paramTypes, function);
    /* Attach it to the list of rules */
    struct PrimitiveRule* previousRule = g_emptyPrimRule;
    struct PrimitiveRule* rule = prim->rules;
    /* Locate the final rule */
    while (rule != g_emptyPrimRule) {
        previousRule = rule;
        rule = rule->nextRule;
    }
    /* Attach the new rule to the list of rules */
    if (previousRule == g_emptyPrimRule) {
        prim->rules = newRule;
    }
    else {
        previousRule->nextRule = newRule;
    }
}

void prim_addRule2(struct Primitive* prim, PrimFunction function, count_t nParams, ...) {
    va_list paramTypes;
    va_start(paramTypes, nParams);
    /* Create the new rule */
    struct PrimitiveRule* newRule = _vnewRule(function, nParams, paramTypes);
    /* Attach it to the list of rules */
    struct PrimitiveRule* previousRule = g_emptyPrimRule;
    struct PrimitiveRule* rule = prim->rules;
    /* Locate the final rule */
    while (rule != g_emptyPrimRule) {
        previousRule = rule;
        rule = rule->nextRule;
    }
    /* Attach the new rule to the list of rules */
    if (previousRule == g_emptyPrimRule) {
        prim->rules = newRule;
    }
    else {
        previousRule->nextRule = newRule;
    }
}

struct PrimitiveRule* prim_emptyRule(void) {
    enum TypeId paramTypes[] = {};
    struct PrimitiveRule* rule = _newRule(0, paramTypes, _emptyPrimFunction);
    return rule;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t prim_apply(struct Primitive* prim, struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    PrimFunction function;
    if (!_checkArgs(prim, nArgs, args, &function)) {
        return false;
    }
    struct Object** argVals;
    if (prim->primType == PrimType_Function) {
        argVals = memory_alloc(nArgs);
        struct Object* error;
        if (!array_evalElems_rec(nArgs, args, argVals, etor, &error)) {
            return false;
        }
    }
    else {
        argVals = args;
    }
    return function(etor, nArgs, argVals, value);
}

void prim_show(struct Primitive* prim, FILE* stream) {
    fputc('@', stream);
    identifier_show(prim->name, stream);
}

/* Private functions *********************************************************/

static bool_t _checkArgs(struct Primitive* prim, count_t nArgs, struct Object* args[], PrimFunction* function) {
    struct PrimitiveRule* rule = prim->rules;
    while (rule != g_emptyPrimRule) {
        if (rule->nParams == COUNT_MAX) {
            /* COUNT_MAX means "any number of arguments is accepted" */
            goto RETURN_TRUE;
        }
        if (rule->nParams != nArgs) {
            continue;
        }
        for (index_t n=0; n<rule->nParams; n++) {
            if (rule->paramTypes[n] != args[n]->typeId) {
                goto NEXT_RULE;
            }
        }
    RETURN_TRUE:
        *function = rule->function;
        return true;
    NEXT_RULE:
        rule = rule->nextRule;
    }
    return false;
}

static bool_t _emptyPrimFunction(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    /* Do nothing */
    return true;
}

#if 0
void _showRule(struct PrimitiveRule* rule) {
    fprintf(stderr, "PrimitiveRule @ %p:\n", rule);
    fprintf(stderr, "  function = %p\n", rule->function);
    fprintf(stderr, "  nParams = %lu ", rule->nParams);
    for (index_t n=0; n<rule->nParams; n++) {
        fprintf(stderr, " %lu:(%u)%s", n, rule->paramTypes[n], typeName(rule->paramTypes[n]));
    }
    fputc('\n', stderr);
}
#endif

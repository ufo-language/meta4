#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
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

struct Primitive* prim_new(const string_t name) {
    struct Primitive* prim = (struct Primitive*)object_new(OT_Primitive, NWORDS(*prim));
    prim->name = identifier_new(name);
    prim->rules = g_emptyPrimRule;
    return prim;
}

struct PrimitiveRule* prim_newRule(count_t nParams, enum TypeId paramTypes[]) {
    struct PrimitiveRule* rule = (struct PrimitiveRule*)memory_alloc(NWORDS(*rule) + nParams);
    rule->nParams = nParams;
    memcpy(rule->paramTypes, paramTypes, sizeof(enum TypeId) * nParams);
    return rule;
}

void prim_addlRule(struct Primitive* prim, count_t nParams, enum TypeId paramTypes[], PrimFunction function) {
    /* Create the new rule */
    struct PrimitiveRule* newRule = prim_newRule(nParams, paramTypes);
    newRule->nParams = nParams;
    memcpy(newRule->paramTypes, paramTypes, nParams * sizeof(struct Object*));
    newRule->function = function;
    newRule->nextRule = g_emptyPrimRule;
    /* Attach it to the list of rules */
    struct PrimitiveRule* previousRule = g_emptyPrimRule;
    struct PrimitiveRule* rule = prim->rules;
    while (rule != g_emptyPrimRule) {
        previousRule = rule;
        rule = rule->nextRule;
    }
    if (previousRule == g_emptyPrimRule) {
        prim->rules = newRule;
    }
    else {
        previousRule->nextRule = newRule;
    }
}

struct PrimitiveRule* prim_emptyRule(void) {
    enum TypeId paramTypes[] = {};
    struct PrimitiveRule* rule = prim_newRule(0, paramTypes);
    rule->function = _emptyPrimFunction;
    rule->nParams = 0;
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
    return function(etor, nArgs, args, value);
}

void prim_show(struct Primitive* prim, FILE* stream) {
    fputc('@', stream);
    identifier_show(prim->name, stream);
}

/* Private functions *********************************************************/

static bool_t _checkArgs(struct Primitive* prim, count_t nArgs, struct Object* args[], PrimFunction* function) {
    struct PrimitiveRule* rule = prim->rules;
    while (rule != g_emptyPrimRule) {
        if (rule->nParams != nArgs) {
            continue;
        }
        for (index_t n=0; n<rule->nParams; n++) {
            if (rule->paramTypes[n] != args[n]->typeId) {
                goto NEXT_RULE;
            }
        }
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

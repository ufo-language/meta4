#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

typedef bool_t (*PrimFunction)(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

enum PrimType {
    PrimType_Function, PrimType_Macro
};

struct PrimitiveRule {
    PrimFunction function;
    struct PrimitiveRule* nextRule;
    count_t nParams;
    enum TypeId paramTypes[];
};

struct Primitive {
    struct Object obj;
    struct Identifier* name;
    struct PrimitiveRule* rules;
    enum PrimType primType;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

struct Primitive* prim_new(const string_t name, enum PrimType primType);
struct Primitive* prim_newFunction(const string_t name);
struct Primitive* prim_newMacro(const string_t name);
void prim_addlRule(struct Primitive* prim, count_t nParams, enum TypeId paramTypes[], PrimFunction function);
struct PrimitiveRule* prim_emptyRule(void);

/* Object functions ******************/

bool_t prim_apply(struct Primitive* prim, struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
void prim_show(struct Primitive* prim, FILE* stream);

#include <stdarg.h>

#include "_typedefs.h"

#include "object/globals.h"
#include "object/primitives/defineprims.h"
#include "object/types/vector.h"

#include "object/primitives/primobject.h"
#include "object/primitives/primpair.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void definePrim(struct Vector* env, const string_t name, PrimFunction function, count_t nParams, ...);
void defineMacro(struct Vector* env, const string_t name, PrimFunction function, count_t nParams, ...);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void definePrim(struct Vector* env, const string_t name, PrimFunction function, count_t nParams, ...) {
    va_list paramTypes;
    va_start(paramTypes, nParams);
    struct Primitive* prim = prim_newFunction(name);
    prim_vaddRule(prim, function, nParams, paramTypes);
    va_end(paramTypes);
    vector_bindPair(env, (struct Object*)prim->name, (struct Object*)prim);
}

void defineMacro(struct Vector* env, const string_t name, PrimFunction function, count_t nParams, ...) {
    va_list paramTypes;
    va_start(paramTypes, nParams);
    struct Primitive* prim = prim_newMacro(name);
    prim_vaddRule(prim, function, nParams, paramTypes);
    va_end(paramTypes);
    vector_bindPair(env, (struct Object*)prim->name, (struct Object*)prim);
}

void definePrims_init(struct Vector* env) {
    prim_object_defineAll(env);
    prim_pair_defineAll(env);
}

/* Private functions *********************************************************/

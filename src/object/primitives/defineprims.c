#include <stdarg.h>

#include "_typedefs.h"

#include "object/functions/display.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/types/primitive.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static bool_t _display(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _show   (struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void definePrim(struct Vector* env, const string_t name, PrimFunction function, count_t nParams, ...) {
    va_list paramTypes;
    va_start(paramTypes, nParams);
    struct Primitive* prim = prim_newFunction(name);
    prim_addRule2(prim, function, nParams, paramTypes);
    vector_bindPair(env, (struct Object*)prim->name, (struct Object*)prim);
}

void definePrims_init(struct Vector* env) {
#if 0
    struct Primitive* prim = prim_newFunction("display");
    prim_addRule2(prim, _display, COUNT_MAX);
    vector_bindPair(env, (struct Object*)prim->name, (struct Object*)prim);
#endif
    definePrim(env, "display", _display, COUNT_MAX);
    definePrim(env, "show", _show, COUNT_MAX);
}

/* Private functions *********************************************************/

static bool_t _display(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    for (index_t n=0; n<nArgs; n++) {
        display(args[n], stdout);
    }
    *value = (struct Object*)g_nil;
    return true;
}

static bool_t _show(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    for (index_t n=0; n<nArgs; n++) {
        show(args[n], stdout);
    }
    *value = (struct Object*)g_nil;
    return true;
}

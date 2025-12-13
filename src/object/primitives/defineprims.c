#include <stdarg.h>

#include "_typedefs.h"

#include "object/functions/count.h"
#include "object/functions/display.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/types/integer.h"
#include "object/types/pair.h"
#include "object/types/primitive.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static bool_t _count  (struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _display(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _first  (struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _rest   (struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _show   (struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

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

void definePrims_init(struct Vector* env) {
    definePrim(env, "count",   _count,   1, OT_Any);
    definePrim(env, "display", _display, COUNT_MAX);
    definePrim(env, "first",   _first,   1, OT_Pair);
    definePrim(env, "rest",    _rest,    1, OT_Pair);
    definePrim(env, "show",    _show,    COUNT_MAX);
}

/* Private functions *********************************************************/

static bool_t _count(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    count_t nElems;
    if (!count(args[0], &nElems)) {
        return false;
    }
    *value = (struct Object*)integer_new((int_t)nElems);
    return true;
}

static bool_t _display(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    for (index_t n=0; n<nArgs; n++) {
        display(args[n], stdout);
    }
    *value = (struct Object*)g_nil;
    return true;
}

static bool_t _first(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    struct Pair* pair = (struct Pair*)args[0];
    *value = pair->first;
    return true;
}

static bool_t _rest(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    struct Pair* pair = (struct Pair*)args[0];
    *value = pair->rest;
    return true;
}

static bool_t _show(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    for (index_t n=0; n<nArgs; n++) {
        show(args[n], stdout);
    }
    *value = (struct Object*)g_nil;
    return true;
}

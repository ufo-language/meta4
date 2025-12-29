#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/count.h"
#include "object/functions/display.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/primitives/defineprims.h"
#include "object/types/integer.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void prim_object_defineAll(struct Vector* env);

static bool_t _count(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _display(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _show(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _throw(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void prim_object_defineAll(struct Vector* env) {
    definePrim(env, "count",   _count,   1, OT_Any);
    definePrim(env, "display", _display, COUNT_MAX);
    definePrim(env, "show",    _show,    COUNT_MAX);
    definePrim(env, "throw",   _throw,   1, OT_Any);
}

static bool_t _count(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    count_t nElems;
    if (!count(args[0], &nElems)) {
        *value = (struct Object*)errorTerm_objAndType("CountError", "Object is not countable", args[0]);
        return false;
    }
    *value = (struct Object*)integer_new((int_t)nElems);
    return true;
}

static bool_t _display(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    for (index_t n=0; n<nArgs; ++n) {
        display(args[n], g_stdout);
    }
    *value = (struct Object*)g_nil;
    return true;
}

static bool_t _show(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    for (index_t n=0; n<nArgs; ++n) {
        show(args[n], g_stdout);
    }
    *value = (struct Object*)g_nil;
    return true;
}

static bool_t _throw(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    *value = args[0];
    return false;
}

/* Private functions *********************************************************/

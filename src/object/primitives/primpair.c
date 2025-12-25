#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/primitives/defineprims.h"
#include "object/primitives/primpair.h"
#include "object/types/pair.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static bool_t _first(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);
static bool_t _rest(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void prim_pair_defineAll(struct Vector* env) {
    definePrim(env, "first", _first, 1, OT_Pair);
    definePrim(env, "rest",  _rest,  1, OT_Pair);
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

/* Private functions *********************************************************/

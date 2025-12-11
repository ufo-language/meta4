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


void definePrims_init(struct Vector* env) {

    struct Primitive* prim = prim_newFunction("display");
    enum TypeId paramTypes[] = {};
    prim_addRule(prim, COUNT_MAX, paramTypes, _display);
    vector_bindPair(env, (struct Object*)prim->name, (struct Object*)prim);

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

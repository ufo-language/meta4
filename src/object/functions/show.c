#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/show.h"

#include "plx.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

ShowFunction g_showFunctions[OT_Max];

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void show(struct Object* obj, FILE* stream) {
    g_showFunctions[obj->typeId](obj, stream);
}

/* Private functions *********************************************************/

extern const struct ShowFunction_handler __start_show_function;
extern const struct ShowFunction_handler __stop_show_function;

static void _init(void) {
    for (const struct ShowFunction_handler *h = &__start_show_function; h < &__stop_show_function; h++) {
        fprintf(stderr, "got show function for '%u'\n", h->typeId);
        // h->function(NULL, NULL);
    }
}
__attribute__((used, section("init_function")))
static const struct InitFunction_handler h_nil_init = {"Nil", _init};

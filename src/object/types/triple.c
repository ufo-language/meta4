#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/outstream.h"
#include "object/types/triple.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Triple* triple_new(struct Object* key, struct Object* value, struct Triple* next) {
    struct Triple* triple = (struct Triple*)object_new(OT_Triple, NWORDS(struct Triple));
    triple->key = key;
    triple->value = value;
    triple->next = next;
    return triple;
}

struct Triple* triple_new_empty(void) {
    struct Triple* triple = (struct Triple*)object_new(OT_Triple, NWORDS(struct Triple));
    triple->key = (struct Object*)g_nil;
    triple->value = (struct Object*)g_nil;
    triple->next = triple;
    return triple;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

void triple_show(struct Triple* triple, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'O', triple->key,
        'C', '=',
        'O', triple->value,
        0
    );
}

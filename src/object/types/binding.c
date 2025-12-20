#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/binding.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Binding* binding_new(struct Object* key, struct Object* value, struct Binding* next) {
    struct Binding* triple = (struct Binding*)object_new(OT_Binding, NWORDS(struct Binding));
    triple->key = key;
    triple->value = value;
    triple->next = next;
    return triple;
}

struct Binding* binding_new_empty(void) {
    struct Binding* triple = (struct Binding*)object_new(OT_Binding, NWORDS(struct Binding));
    triple->key = (struct Object*)g_nil;
    triple->value = (struct Object*)g_nil;
    triple->next = triple;
    return triple;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

void binding_show(struct Binding* triple, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'O', triple->key,
        'C', '=',
        'O', triple->value,
        0
    );
}

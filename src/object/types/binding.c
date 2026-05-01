#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/binding.h"
#include "object/types/identifier.h"
#include "object/types/outstream.h"
#include "object/types/symbol.h"

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

bool_t binding_eval_rec(struct Binding* binding, struct Etor_rec* etor, struct Object** value) {
    if (!eval_rec(binding->value, etor, value)) {
        return false;
    }
    struct Object* evalValue = *value;
    
    if (binding->key->typeId == OT_Symbol) {
        struct Symbol* keySym = (struct Symbol*)binding->key;
        struct Identifier* keyIdent = identifier_new(keySym->name);
        etor_rec_bind(etor, keyIdent, evalValue);
        *value = (struct Object*)binding;
        return true;
    }
    
    *value = (struct Object*)errorTerm("BindingError", "Key must be a symbol", 1, "Key", binding->key);
    return false;
}

void binding_show(struct Binding* triple, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'O', triple->key,
        'C', '=',
        'O', triple->value,
        0);
}

/* Private functions --------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/identifier.h"
#include "object/types/outstream.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Identifier* identifier_new(const string_t name) {
    return (struct Identifier*)symbolic_new(name, OT_Identifier, g_identifierInternTable);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* identifier_close_rec(struct Identifier* ident, struct Etor_rec* etor) {
    struct Object* value;
    bool_t success = etor_rec_lookup(etor, ident, &value);
    return success ? value : (struct Object*)ident;
}

bool_t identifier_eval_rec(struct Identifier* ident, struct Etor_rec* etor, struct Object** value) {
    bool_t success = etor_rec_lookup(etor, ident, value);
    if (!success) {
        fprintf(stderr, "ERROR: unbound identifier '%s'\n", ident->name);
        return false;
    }
    return true;
}

/* Private functions *********************************************************/

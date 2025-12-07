#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/identifier.h"
#include "object/types/string.h"
#include "object/types/vector.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* identifier_new(const string_t name) {
    return symbolic_new(name, OT_Identifier, g_identifierInternTable);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t identifier_eval_rec(struct Symbolic* ident, struct Etor_Rec* etor, struct Object** value) {
    bool_t success = etor_rec_lookup(etor, ident, value);
    switch (etor->operationType) {
        case Etor_Closing:
            if (!success) {
                *value = (struct Object*)ident;
            }
            return true;
        case Etor_Evaluating:
            if (!success) {
                fprintf(stderr, "ERROR: unbound identifier '%s'\n", ident->name);
                assert(false);
                exit(1);
            }
            return true;
    }
}

void identifier_show(struct Symbolic* ident, FILE* stream) {
    fputs(ident->name, stream);
}

/* Private functions *********************************************************/

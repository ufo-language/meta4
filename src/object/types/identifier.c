#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/evaluator/evaluator_recursive.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/identifier.h"
#include "object/types/string.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static struct Identifier* _intern(const string_t name);
struct Identifier* _identifier_new_aux(const string_t name, index_t hashCode);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Identifier* identifier_new(const string_t name) {
    return _intern(name);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

#if 0
bool_t identifier_equal(struct Identifier* ident, struct Identifier* otherIdent) {
    if (ident == otherIdent) {
        /* This check could be redundant, depending on who calls this. */
        return true;
    }
    if (ident->hashCode != otherIdent->hashCode) {
        return false;
    }
    return strcmp(ident->name, otherIdent->name) ? false : true;
}
#endif

bool_t identifier_eval_recursive(struct Identifier* ident, struct Evaluator* etor, struct Object** value) {
    bool_t success = evaluator_lookup(etor, ident, value);
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

void identifier_show(struct Identifier* ident, FILE* stream) {
    fputs(ident->name, stream);
}

/* Private functions *********************************************************/

struct Identifier* _identifier_new_aux(const string_t name, index_t hashCode) {
    struct Identifier* ident = (struct Identifier*)object_new(OT_Identifier, NWORDS(struct Identifier));
    ident->name = name;
    ident->hashCode = hashCode;
    return ident;
}

static struct Identifier* _intern(const string_t nameChars) {
    /* Search the vector for the name */
    struct Object** elems = g_identifierInternTable->elems->elems;
    count_t top = g_identifierInternTable->top;
    for (index_t n=0; n<top; n+=2) {
        if (string_equal_chars((struct String*)elems[n], nameChars)) {
            return (struct Identifier*)elems[n+1];
        }
    }
    /* Create a new Identifier */
    struct String* name = string_new(nameChars);
    struct Identifier* ident = _identifier_new_aux(nameChars, top);
    /* Add the name to the array */
    vector_push(g_identifierInternTable, (struct Object*)name);
    vector_push(g_identifierInternTable, (struct Object*)ident);
    return ident;
}

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/evaluator/evaluator_recursive.h"
#include "object/types/identifier.h"

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

struct InternPair {
    string_t name;
    struct Identifier* ident;
};

static string_t _strdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    return p ? memcpy(p, s, n) : NULL;
}

struct Identifier* _identifier_new_aux(const string_t name, index_t hashCode) {
    struct Identifier* ident = (struct Identifier*)object_new(OT_Identifier, NWORDS(struct Identifier));
    ident->name = name;
    ident->hashCode = hashCode;
    return ident;
}

/* TODO Interning currently involves doing a linear search through an array.
   This could be improved. */
static struct Identifier* _intern(const string_t name) {
    static index_t arrayTop = 0;
    static count_t arraySize = 64;
    static struct InternPair* array;
    if (arrayTop == 0) {
        array = (struct InternPair*)malloc(sizeof(*array) * arraySize);
    }
    /* Search the array for the name */
    for (index_t n=0; n<arrayTop; ++n) {
        if (!strcmp(name, array[n].name)) {
            return array[n].ident;
        }
    }
    /* Expand the array if it's full */
    if (arrayTop == arraySize) {
        struct InternPair* newArray = (struct InternPair*)malloc(sizeof(*array) * arraySize * 2);
        memcpy(newArray, array, sizeof(struct InternPair) * arrayTop);
        free(array);
        array = newArray;
    }
    /* Create a new Identifier */
    string_t newName = _strdup(name);
    struct Identifier* ident = _identifier_new_aux(newName, arrayTop);
    /* Add the name to the array */
    array[arrayTop++] = (struct InternPair) {newName, ident};
    return ident;
}

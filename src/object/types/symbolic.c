#include <string.h>

#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static struct _Symbolic* _symbolic_new_aux(enum TypeId typeId, const string_t name, index_t hashCode);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct _Symbolic* symbolic_new(const string_t name, enum TypeId typeId, struct Vector* internTable) {
    /* Search the intern Vector for the name */
    struct Object** elems = internTable->elems->elems;
    count_t top = internTable->top;
    for (index_t n=0; n<top; n+=2) {
        if (string_equal_chars((struct String*)elems[n], name)) {
            return (struct _Symbolic*)elems[n+1];
        }
    }
    /* Create a new _Symbolic */
    struct String* nameString = string_new(name);
    struct _Symbolic* symbolic = _symbolic_new_aux(typeId, name, top);
    /* Add the name to the intern Vector */
    vector_push(internTable, (struct Object*)nameString);
    vector_push(internTable, (struct Object*)symbolic);
    return symbolic;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void symbolic_show(struct _Symbolic* symbolic, FILE* stream) {
    fputs(symbolic->name, stream);
}

/* Private functions *********************************************************/

static struct _Symbolic* _symbolic_new_aux(enum TypeId typeId, const string_t name, index_t hashCode) {
    count_t nChars = strlen(name);
    struct _Symbolic* symbolic = (struct _Symbolic*)object_new(typeId, NWORDS(*symbolic) + NBYTES_TO_WORDS(nChars + 1));
    symbolic->hashCode = hashCode;
    memcpy(symbolic->name, name, nChars + 1);
    return symbolic;
}

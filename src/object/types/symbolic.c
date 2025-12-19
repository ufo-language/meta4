#include <string.h>

#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/hashtable.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* symbolic_new(const string_t name, enum TypeId typeId, struct HashTable* internTable) {
    count_t nChars = strlen(name);
    return hashTable_intern(internTable, nChars, name, typeId);
}

struct Symbolic* symbolic_new_aux(enum TypeId typeId, count_t nChars, const string_t name, word_t hashCode) {
    struct Symbolic* symbolic = (struct Symbolic*)object_new(typeId, NWORDS(*symbolic) + NBYTES_TO_WORDS(nChars + 1));
    symbolic->hashCode = hashCode;
    memcpy(symbolic->name, name, nChars + 1);
    return symbolic;
}


/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void symbolic_show(struct Symbolic* symbolic, FILE* stream) {
    fputs(symbolic->name, stream);
}

/* Private functions *********************************************************/

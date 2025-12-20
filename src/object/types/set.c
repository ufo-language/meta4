#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/outstream.h"
#include "object/types/set.h"
#include "object/types/binding.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Set* set_new(void) {
    struct Set* set = (struct Set*)object_new(OT_Set, NWORDS(struct Set));
    hashTable_init(&set->hashTable);
    set->hashTable.obj.typeId = OT_Set;
    return set;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void set_add(struct Set* set, struct Object* elem) {
    hashTable_put(&set->hashTable, elem, elem);
}

bool_t set_contains(struct Set* set, struct Object* elem) {
    struct Object* value;
    return hashTable_get(&set->hashTable, elem, &value);
}

bool_t set_remove(struct Set* set, struct Object* elem) {
    return hashTable_remove(&set->hashTable, elem);
}

/* Object functions ******************/

count_t set_count(struct Set* set) {
    return hashTable_count(&set->hashTable);
}

void set_show(struct Set* set, struct OutStream* outStream) {
    outStream_writeString(outStream, "${");
    bool_t firstShown = false;
    for (index_t n=0; n<set->hashTable.nBuckets; ++n) {
        struct Binding* binding = set->hashTable.buckets[n];
        while (binding != g_emptyTriple) {
            if (firstShown) {
                outStream_writeString(outStream, ", ");
            }
            show(binding->key, outStream);
            binding = binding->next;
            firstShown = true;
        }
    }
    outStream_writeChar(outStream, '}');
}

/* Private functions *********************************************************/

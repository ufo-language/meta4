#include <stdio.h>

#include "_typedefs.h"

#include "memory/gc.h"
#include "memory/memory.h"
#include "object/functions/equal.h"
#include "object/functions/hash.h"
#include "object/globals.h"
#include "object/types/hashtable.h"
#include "object/types/triple.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* for reference
struct HashTable {
    struct Object* obj;
    real_t loadFactor;
    count_t load;
    count_t maxLoad;
    count_t nBuckets;
    struct Bucket* buckets[];
};
*/

/* Forward declarations ******************************************************/

struct Triple** _createNBuckets(count_t nBuckets);
static void _resize(struct HashTable* hashTable);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct HashTable* hashTable_new(void) {
    struct HashTable* hashTable = (struct HashTable*)object_new(OT_HashTable, sizeof(struct HashTable));
    hashTable->loadFactor = DEFAULT_HASHTABLE_LOAD_FACTOR;
    hashTable->nElems = 0;
    hashTable->maxLoad = (count_t)(DEFAULT_HASHTABLE_LOAD_FACTOR * (real_t)DEFAULT_HASHTABLE_NBUCKETS);
    hashTable->nBuckets = DEFAULT_HASHTABLE_NBUCKETS;
    gc_pushRoot(g_gc, (struct Object*)hashTable);
    hashTable->buckets = _createNBuckets(hashTable->nBuckets);
    gc_popRoot(g_gc);
    return hashTable;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t hashTable_get(struct HashTable* hashTable, struct Object* key, struct Object** value) {
    word_t hashCode;
    if (!hash(key, &hashCode)) {
        return false;
    }
    index_t bucketNum = hashCode % hashTable->nBuckets;
    /* Look for existing key */
    struct Triple* binding = hashTable->buckets[bucketNum];
    while (binding != g_emptyTriple) {
        if (equal(key, binding->key)) {
            *value = binding->value;
            return true;
        }
        binding = binding->next;
    }
    return false;
}

bool_t hashTable_put(struct HashTable* hashTable, struct Object* key, struct Object* value) {
    word_t hashCode;
    if (!hash(key, &hashCode)) {
        return false;
    }
    if (hashTable->nElems == hashTable->loadFactor) {
        _resize(hashTable);
    }
    index_t bucketNum = hashCode % hashTable->nBuckets;
    /* Look for existing key */
    struct Triple* binding = hashTable->buckets[bucketNum];
    while (binding != g_emptyTriple) {
        if (equal(key, binding->key)) {
            binding->value = value;
            return true;
        }
        binding = binding->next;
    }
    binding = triple_new(key, value, hashTable->buckets[bucketNum]);
    return true;
}

bool_t hashTable_remove(struct HashTable* hashTable, struct Object* key) {
}

/* Object functions ******************/

#include <assert.h>
struct Object* hashTable_close_rec(struct HashTable* hashTable, struct Etor_rec* etor) {
    assert(false);
}

bool_t hashTable_eval_rec(struct HashTable* hashTable, struct Etor_rec* etor, struct Object** value) {
    assert(false);
}

void hashTable_show(struct HashTable* hashTable, FILE* stream) {
}

/* Private functions *********************************************************/

struct Triple** _createNBuckets(count_t nBuckets) {
    count_t nWords = NBYTES_TO_WORDS(sizeof(struct Triple*) * nBuckets);
    struct Triple** buckets = memory_alloc(nWords);
    for (index_t n=0; n<nBuckets; n++) {
        buckets[n] = g_emptyTriple;
    }
    return buckets;
}

static void _resize(struct HashTable* hashTable) {
    /* Allocate new buckets */
    /* Rehash each pair */
    /* Set new loadFactor */
}

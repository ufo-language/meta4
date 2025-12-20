#include <stdio.h>

#include "_typedefs.h"

#include "lexer/lexer.h"
#include "memory/gc.h"
#include "memory/memory.h"
#include "object/functions/equal.h"
#include "object/functions/hash.h"
#include "object/globals.h"
#include "object/types/hashtable.h"
#include "object/types/outstream.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"
#include "object/types/binding.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static struct Binding** _hashTable_createNBuckets(count_t nBuckets);
static void _hashTable_resize(struct HashTable* hashTable);
static void _hashTable_putUsingBuckets(count_t nBuckets, struct Binding** buckets, struct Object* key, word_t hashCode, struct Object* value);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct HashTable* hashTable_new(void) {
    struct HashTable* hashTable = (struct HashTable*)object_new(OT_HashTable, NWORDS(struct HashTable));
    hashTable_init(hashTable);
    return hashTable;
}

void hashTable_init(struct HashTable* hashTable) {
    hashTable->loadFactor = DEFAULT_HASHTABLE_LOAD_FACTOR;
    hashTable->nElems = 0;
    hashTable->maxLoad = (count_t)(DEFAULT_HASHTABLE_LOAD_FACTOR * (real_t)DEFAULT_HASHTABLE_NBUCKETS);
    hashTable->nBuckets = DEFAULT_HASHTABLE_NBUCKETS;
    gc_pushRoot(g_gc, (struct Object*)hashTable);
    hashTable->buckets = _hashTable_createNBuckets(hashTable->nBuckets);
    gc_popRoot(g_gc);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t hashTable_get(struct HashTable* hashTable, struct Object* key, struct Object** value) {
    word_t hashCode;
    if (!hash(key, &hashCode)) {
        return false;
    }
    return hashTable_get_withHashCode(hashTable, key, hashCode, value);
}

bool_t hashTable_get_withHashCode(struct HashTable* hashTable, struct Object* key, word_t hashCode, struct Object** value) {
    index_t bucketNum = hashCode % hashTable->nBuckets;
    /* Look for existing key */
    struct Binding* binding = hashTable->buckets[bucketNum];
    while (binding != g_emptyTriple) {
        if (equal(key, binding->key)) {
            *value = binding->value;
            return true;
        }
        binding = binding->next;
    }
    return false;
}

struct Symbolic* hashTable_intern(struct HashTable* internTable, count_t nChars, const string_t name, enum TypeId typeId) {
    struct {
        struct Object obj;
        count_t nChars;
        char chars[Lexer_LexemeSize + 1];
    } probeString;
    /* Create a probe string to check the table for the key */
    string_init((struct String*)&probeString, nChars, name);
    word_t hashCode;
    hash((struct Object*)&probeString, &hashCode);
    struct Object* value;
    if (hashTable_get_withHashCode(internTable, (struct Object*)&probeString, hashCode, &value)) {
        return (struct Symbolic*)value;
    }
    /* Create a real string and add it to the table */
    struct String* realKey = string_new_empty(nChars);
    string_init(realKey, nChars, name);
    struct Symbolic* symbolicValue = symbolic_new_aux(typeId, nChars, name, hashCode);
    hashTable_put(internTable, (struct Object*)realKey, (struct Object*)symbolicValue);
    return symbolicValue;
}

bool_t hashTable_put(struct HashTable* hashTable, struct Object* key, struct Object* value) {
    word_t hashCode;
    if (!hash(key, &hashCode)) {
        return false;
    }
    if (hashTable->nElems == hashTable->maxLoad) {
        _hashTable_resize(hashTable);
    }
    _hashTable_putUsingBuckets(hashTable->nBuckets, hashTable->buckets, key, hashCode, value);
    ++hashTable->nElems;
    return true;
}

bool_t hashTable_remove(struct HashTable* hashTable, struct Object* key) {
    word_t hashCode;
    if (!hash(key, &hashCode)) {
        return false;
    }
    index_t bucketNum = hashCode % hashTable->nBuckets;
    struct Binding* binding = hashTable->buckets[bucketNum];
    struct Binding* prev = g_emptyTriple;
    while (binding != g_emptyTriple) {
        if (equal(key, binding->key)) {
            if (prev == g_emptyTriple) {
                hashTable->buckets[bucketNum] = binding->next;
            }
            else {
                prev->next = binding->next;
            }
            --hashTable->nElems;
            return true;
        }
        prev = binding;
        binding = binding->next;
    }
    return false;
}

/* Object functions ******************/

count_t hashTable_count(struct HashTable* hashTable) {
    return hashTable->nElems;
}

void hashTable_show(struct HashTable* hashTable, struct OutStream* outStream) {
    outStream_writeString(outStream, "#{");
    bool_t firstShown = false;
    for (index_t n=0; n<hashTable->nBuckets; ++n) {
        struct Binding* binding = hashTable->buckets[n];
        while (binding != g_emptyTriple) {
            if (firstShown) {
                outStream_writeString(outStream, ", ");
            }
            binding_show(binding, outStream);
            binding = binding->next;
            firstShown = true;
        }
    }
    outStream_writeChar(outStream, '}');
}

/* Private functions *********************************************************/

static struct Binding** _hashTable_createNBuckets(count_t nBuckets) {
    count_t nWords = NBYTES_TO_WORDS(sizeof(struct Binding*) * nBuckets);
    struct Binding** buckets = memory_alloc(nWords);
    for (index_t n=0; n<nBuckets; ++n) {
        buckets[n] = g_emptyTriple;
    }
    return buckets;
}

static void _hashTable_putUsingBuckets(count_t nBuckets, struct Binding** buckets, struct Object* key, word_t hashCode, struct Object* value) {
    index_t bucketNum = hashCode % nBuckets;
    /* Look for existing key */
    struct Binding* binding = buckets[bucketNum];
    while (binding != g_emptyTriple) {
        if (equal(key, binding->key)) {
            binding->value = value;
            return;
        }
        binding = binding->next;
    }
    binding = binding_new(key, value, buckets[bucketNum]);
    buckets[bucketNum] = binding;
}

static void _hashTable_resize(struct HashTable* hashTable) {
    count_t newNBuckets = hashTable->nBuckets * 2;
    /* Allocate new buckets */
    struct Binding** newBuckets = _hashTable_createNBuckets(newNBuckets);
    /* Rehash each pair */
    for (index_t n=0; n<hashTable->nBuckets; ++n) {
        struct Binding* binding = hashTable->buckets[n];
        while (binding != g_emptyTriple) {
            word_t hashCode;
            /* It's safe to ignore the return value of hash() because we already know
               that the key is hashable */
            hash(binding->key, &hashCode);
            _hashTable_putUsingBuckets(newNBuckets, newBuckets, binding->key, hashCode, binding->value);
            binding = binding->next;
            ++hashTable->nElems;
        }
    }
    /* Assign the new buckets to this hash table */
    hashTable->buckets = newBuckets;
    hashTable->nBuckets = newNBuckets;
    /* Set new maxLoad */
    hashTable->maxLoad = (count_t)(hashTable->loadFactor * (real_t)newNBuckets);
}

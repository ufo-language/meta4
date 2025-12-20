#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

#define DEFAULT_HASHTABLE_NBUCKETS 8
#define DEFAULT_HASHTABLE_LOAD_FACTOR 0.7

/* Types *********************************************************************/

struct Binding;

struct HashTable {
    struct Object obj;
    real_t loadFactor;
    count_t nElems;
    count_t maxLoad;
    count_t nBuckets;
    struct Binding** buckets;
};

struct OutStream;
struct Symbolic;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct HashTable* hashTable_new(void);
void hashTable_init(struct HashTable* hashTable);

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t hashTable_get(struct HashTable* hashTable, struct Object* key, struct Object** value);
bool_t hashTable_get_withHashCode(struct HashTable* hashTable, struct Object* key, word_t hashCode, struct Object** value);
bool_t hashTable_put(struct HashTable* hashTable, struct Object* key, struct Object* value);
bool_t hashTable_remove(struct HashTable* hashTable, struct Object* key);

struct Symbolic* hashTable_intern(struct HashTable* internTable, count_t nChars, const string_t chars, enum TypeId typeId);

/* Object functions ******************/

count_t hashTable_count(struct HashTable* hashTable);
void hashTable_show(struct HashTable* hashTable, struct OutStream* outStream);

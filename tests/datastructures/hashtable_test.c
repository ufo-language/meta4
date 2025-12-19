#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/hashtable.h"
#include "object/types/integer.h"
#include "object/types/symbol.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(hashTable_checkConstruction)
        struct HashTable* hashTable = hashTable_new();
        ASSERT_ISA(OT_HashTable, hashTable);
        EXPECT_IEQ(DEFAULT_HASHTABLE_NBUCKETS, hashTable->nBuckets);
        EXPECT_REQ(DEFAULT_HASHTABLE_LOAD_FACTOR, hashTable->loadFactor);
        EXPECT_IEQ(0, hashTable->nElems);
        EXPECT_IEQ(DEFAULT_HASHTABLE_NBUCKETS * DEFAULT_HASHTABLE_LOAD_FACTOR, hashTable->maxLoad);
        EXPECT_IEQ(0, strcmp("HashTable", typeName(hashTable->obj.typeId)));
    END

    TEST(hashTable_checkGet_empty)
        struct HashTable* hashTable = hashTable_new();
        struct Object* key = (struct Object*)g_nil;
        struct Object* value;
        ASSERT_FALSE(hashTable_get(hashTable, key, &value));
    END

    TEST(hashTable_checkGet_nonEmpty)
        struct HashTable* hashTable = hashTable_new();
        struct Symbol* a = symbol_new("A");
        struct Integer* i100 = integer_new(100);
        ASSERT_TRUE(hashTable_put(hashTable, OBJ(a), OBJ(i100)));
        struct Object* retrievedValue;
        ASSERT_TRUE(hashTable_get(hashTable, OBJ(a), &retrievedValue));
        ASSERT_EQ(i100, retrievedValue);
        struct Symbol* b = symbol_new("B");
        ASSERT_FALSE(hashTable_get(hashTable, OBJ(b), &retrievedValue));
    END

    TEST(hashTable_checkResize)
        struct HashTable* hashTable = hashTable_new();
        count_t hashTableInitialNBuckets = hashTable->nBuckets;
        struct Vector* keys = vector_new();
        struct Vector* values = vector_new();
        char name[2] = {'A', 0};
        int_t iValue = 100;
        /* Add values to the hash table up to the load factor */
        for (count_t n=0; n<hashTable->maxLoad; ++n) {
            struct Symbol* key = symbol_new(name);
            struct Integer* value = integer_new(iValue);
            hashTable_put(hashTable, OBJ(key), OBJ(value));
            vector_push(keys, (struct Object*)key);
            vector_push(values, (struct Object*)value);
            ++name[0];
            value += 100;
        }
        ASSERT_IEQ(hashTableInitialNBuckets, hashTable->nBuckets);
        struct Symbol* key = symbol_new(name);
        struct Integer* value = integer_new(iValue);
        /* Add one more value; should trigger resize */
        hashTable_put(hashTable, (struct Object*)key, (struct Object*)value);
        vector_push(keys, (struct Object*)key);
        vector_push(values, (struct Object*)value);
        ASSERT_IEQ(hashTableInitialNBuckets * 2, hashTable->nBuckets);
        /* Verify that the bindings are still the same */
        for (index_t n=0; n<vector_count(keys); ++n) {
            struct Object* key = vector_get_unsafe(keys, n);
            struct Object* value = vector_get_unsafe(values, n);
            struct Object* value1;
            ASSERT_TRUE(hashTable_get(hashTable, key, &value1));
            EXPECT_EQ(value, value1);
        }
    END

    TEST(hashTable_checkRemove)
        struct HashTable* hashTable = hashTable_new();
        struct Symbol* a = symbol_new("A");
        struct Symbol* b = symbol_new("B");
        struct Symbol* c = symbol_new("C");
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        struct Integer* i300 = integer_new(300);
        hashTable_put(hashTable, OBJ(a), OBJ(i100));
        hashTable_put(hashTable, OBJ(b), OBJ(i200));
        hashTable_put(hashTable, OBJ(c), OBJ(i300));
        ASSERT_IEQ(3, hashTable->nElems);
        ASSERT_TRUE(hashTable_remove(hashTable, OBJ(b)));
        ASSERT_IEQ(2, hashTable->nElems);
        struct Object* value;
        EXPECT_TRUE(hashTable_get(hashTable, OBJ(a), &value));
        EXPECT_FALSE(hashTable_get(hashTable, OBJ(b), &value));
        EXPECT_TRUE(hashTable_get(hashTable, OBJ(c), &value));
    END

    TEST(hashTable_checkShow)
        struct HashTable* hashTable = hashTable_new();
        hashTable_put(hashTable, OBJ(symbol_new("A")), OBJ(integer_new(100)));
        hashTable_put(hashTable, OBJ(symbol_new("B")), OBJ(integer_new(200)));
        hashTable_put(hashTable, OBJ(symbol_new("C")), OBJ(integer_new(300)));
        SHOW("Should show '#{A=100, B=200, C=300}'", hashTable);
    END

    END_TESTS
}

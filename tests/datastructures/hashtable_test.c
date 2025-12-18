#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/hashtable.h"

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

    END_TESTS
}

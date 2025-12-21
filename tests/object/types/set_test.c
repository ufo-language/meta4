#include "_test.h"
#include "_typedefs.h"

#include "object/types/set.h"
#include "object/types/symbol.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(set_checkConstruction)
        struct Set* set = set_new();
        EXPECT_ISA(OT_Set, set);
        EXPECT_IEQ(NWORDS(struct Object) + 5, set->hashTable.obj.nWords);
        EXPECT_IEQ(NWORDS(struct Set), set->hashTable.obj.nWords);
        EXPECT_IEQ(0, set_count(set));
    END

    TEST(set_checkAddContains)
        struct Set* set = set_new();
        struct Symbol* a = symbol_new("A");
        set_add(set, OBJ(a));
        EXPECT_TRUE(set_contains(set, OBJ(a)));
    END

    TEST(set_checkRemove)
        struct Set* set = set_new();
        struct Symbol* a = symbol_new("A");
        set_add(set, OBJ(a));
        ASSERT_TRUE(set_contains(set, OBJ(a)));
        ASSERT_TRUE(set_remove(set, OBJ(a)));
        EXPECT_FALSE(set_contains(set, OBJ(a)));
    END

    END_TESTS
}

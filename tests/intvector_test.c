#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/intvector.h"
#include "object/evaluator/etor_rec.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(intVector_checkConstruction)
        struct IntVector* intVector = intVector_new();
        ASSERT_ISA(OT_IntVector, intVector);
        ASSERT_IEQ(0, intVector_count(intVector));
        ASSERT_IEQ(0, intVector->nResizes);
        EXPECT_IEQ(0, strcmp("IntVector", typeName(intVector->obj.typeId)));
    END

    TEST(intVector_checkPushAndPop)
        struct IntVector* intVector = intVector_new();
        ASSERT_IEQ(0, intVector_count(intVector));
        intVector_push(intVector, 100);
        intVector_push(intVector, 200);
        intVector_push(intVector, 300);
        int_t value;
        ASSERT_TRUE(intVector_pop(intVector, &value));
        EXPECT_IEQ(300, value);
        ASSERT_TRUE(intVector_pop(intVector, &value));
        EXPECT_IEQ(200, value);
        ASSERT_TRUE(intVector_pop(intVector, &value));
        EXPECT_IEQ(100, value);
        EXPECT_FALSE(intVector_pop(intVector, &value));
    END

    TEST(intVector_checkSetAndGet)
        struct IntVector* intVector = intVector_new();
        intVector_push(intVector, 0);
        intVector_push(intVector, 0);
        intVector_push(intVector, 0);
        int_t value;
        ASSERT_TRUE(intVector_get(intVector, 0, &value));
        EXPECT_IEQ(0, value);
        ASSERT_TRUE(intVector_get(intVector, 1, &value));
        EXPECT_IEQ(0, value);
        ASSERT_TRUE(intVector_get(intVector, 2, &value));
        EXPECT_IEQ(0, value);

        ASSERT_TRUE(intVector_set(intVector, 0, 100));
        ASSERT_TRUE(intVector_get(intVector, 0, &value));
        ASSERT_IEQ(100, value);
        ASSERT_TRUE(intVector_get(intVector, 1, &value));
        EXPECT_IEQ(0, value);
        ASSERT_TRUE(intVector_get(intVector, 2, &value));
        EXPECT_IEQ(0, value);

        ASSERT_TRUE(intVector_set(intVector, 1, 200));
        ASSERT_TRUE(intVector_get(intVector, 0, &value));
        EXPECT_IEQ(100, value);
        ASSERT_TRUE(intVector_get(intVector, 1, &value));
        ASSERT_IEQ(200, value);
        ASSERT_TRUE(intVector_get(intVector, 2, &value));
        EXPECT_IEQ(0, value);

        ASSERT_TRUE(intVector_set(intVector, 2, 300));
        ASSERT_TRUE(intVector_get(intVector, 0, &value));
        EXPECT_IEQ(100, value);
        ASSERT_TRUE(intVector_get(intVector, 1, &value));
        EXPECT_IEQ(200, value);
        ASSERT_TRUE(intVector_get(intVector, 2, &value));
        ASSERT_IEQ(300, value);
    END

    TEST(intVector_checkResize)
        struct IntVector* intVector = intVector_new_withCapacity(4);
        ASSERT_IEQ(0, intVector_count(intVector));
        count_t capacity = intVector->capacity;
        ASSERT_IEQ(4, capacity);
        for (count_t n=0; n<capacity; n++) {
            intVector_push(intVector, n * 100);
        }
        ASSERT_IEQ(0, intVector->nResizes);
        intVector_push(intVector, (capacity + 1) * 100);
        ASSERT_IEQ(1, intVector->nResizes);
        ASSERT_IEQ(capacity * 2, intVector->capacity);
        int_t value;
        ASSERT_TRUE(intVector_pop(intVector, &value));
        ASSERT_IEQ((capacity + 1) * 100, value);
    END

    TEST(intVector_checkShow)
        struct IntVector* intVector = intVector_new();
        intVector_push(intVector, 100);
        intVector_push(intVector, 200);
        intVector_push(intVector, 300);
        SHOW("Should show '{%|300, 200, 100|}'", intVector);
    END

    END_TESTS
}

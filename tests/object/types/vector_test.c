#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/typeids.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i0 = integer_new(0);
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);
    struct Integer* i300 = integer_new(300);

    TEST(vector_checkConstruction)
        struct Vector* vector = vector_new();
        ASSERT_ISA(OT_Vector, vector);
        ASSERT_IEQ(0, vector_count(vector));
        ASSERT_IEQ(0, vector->nResizes);
        EXPECT_IEQ(0, strcmp("Vector", typeName(vector->obj.typeId)));
        EXPECT_IEQ(NWORDS(struct Object) + 3, vector->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Vector), vector->obj.nWords);
    END

    TEST(vector_checkPushAndPop)
        struct Vector* vector = vector_new();
        ASSERT_IEQ(0, vector_count(vector));
        vector_push(vector, OBJ(i100));
        vector_push(vector, OBJ(i200));
        vector_push(vector, OBJ(i300));
        struct Object* value;
        ASSERT_TRUE(vector_pop(vector, &value));
        EXPECT_EQ(i300, value);
        ASSERT_TRUE(vector_pop(vector, &value));
        EXPECT_EQ(i200, value);
        ASSERT_TRUE(vector_pop(vector, &value));
        EXPECT_EQ(i100, value);
        EXPECT_FALSE(vector_pop(vector, &value));
    END

    TEST(vector_checkSetAndGet)
        struct Vector* vector = vector_new();
        vector_push(vector, OBJ(i0));
        vector_push(vector, OBJ(i0));
        vector_push(vector, OBJ(i0));
        struct Object* value;
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 0, &value));
        EXPECT_EQ(i0, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 1, &value));
        EXPECT_EQ(i0, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 2, &value));
        EXPECT_EQ(i0, value);

        vector_set_raw(vector, 0, OBJ(i100));
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 0, &value));
        ASSERT_EQ(i100, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 1, &value));
        EXPECT_EQ(i0, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 2, &value));
        EXPECT_EQ(i0, value);

        vector_set_raw(vector, 1, OBJ(i200));
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 0, &value));
        EXPECT_EQ(i100, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 1, &value));
        ASSERT_EQ(i200, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 2, &value));
        EXPECT_EQ(i0, value);

        vector_set_raw(vector, 2, OBJ(i300));
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 0, &value));
        EXPECT_EQ(i100, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 1, &value));
        EXPECT_EQ(i200, value);
        ASSERT_IEQ(SubscriptResult_OK, vector_get(vector, 2, &value));
        ASSERT_EQ(i300, value);
    END

    TEST(vector_checkSetRaw)
        struct Vector* vector = vector_new();
        vector_set_raw(vector, 2, OBJ(i100));
        ASSERT_IEQ(3, vector->nElems);
        EXPECT_IEQ(g_nil, vector->elems->elems[0]);
        EXPECT_IEQ(g_nil, vector->elems->elems[1]);
        EXPECT_IEQ(i100, vector->elems->elems[2]);
    END

    TEST(vector_checkResize)
        struct Vector* vector = vector_new_withCapacity(4);
        ASSERT_IEQ(0, vector_count(vector));
        count_t capacity = vector_capacity(vector);
        ASSERT_IEQ(4, capacity);
        for (count_t n=0; n<capacity; ++n) {
            vector_push(vector, OBJ(integer_new(n * 100)));
        }
        ASSERT_IEQ(0, vector->nResizes);
        vector_push(vector, OBJ(integer_new((capacity + 1) * 100)));
        ASSERT_IEQ(1, vector->nResizes);
        ASSERT_IEQ(capacity * 2, vector_capacity(vector));
        struct Object* value;
        ASSERT_TRUE(vector_pop(vector, &value));
        ASSERT_ISA(OT_Integer, value);
        ASSERT_IEQ((capacity + 1) * 100, ((struct Integer*)value)->i);
    END

    TEST(vector_checkLookup)
        struct Identifier* a = identifier_new("a");
        struct Identifier* b = identifier_new("b");
        struct Identifier* c = identifier_new("c");
        struct Vector* vector = vector_new();
        vector_push(vector, OBJ(a));
        vector_push(vector, OBJ(i100));
        vector_push(vector, OBJ(b));
        vector_push(vector, OBJ(i200));
        struct Object* value;
        ASSERT_TRUE(vector_lookup(vector, OBJ(a), &value));
        EXPECT_EQ(OBJ(i100), value);
        ASSERT_TRUE(vector_lookup(vector, OBJ(b), &value));
        EXPECT_EQ(OBJ(i200), value);
        ASSERT_FALSE(vector_lookup(vector, OBJ(c), &value));
    END

    TEST(vector_checkShow)
        struct Vector* vector = vector_new();
        vector_push(vector, OBJ(i100));
        vector_push(vector, OBJ(i200));
        vector_push(vector, OBJ(i300));
        EXPECT_SHOW("{|100, 200, 300|}", vector);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/evaluator_recursive.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(evaluator_checkConstruction)
        struct Evaluator* etor = evaluator_new();
        ASSERT_IEQ(OT_Evaluator, etor->obj.typeId);
    END

    TEST(evaluator_showSize)
        struct Evaluator* etor = evaluator_new();
        MESSAGE("Evaluator NWORDS:")
        fprintf(stderr, "       ⏩ %lu\n", etor->obj.nWords);
        MESSAGE("Evaluator NBYTES:")
        fprintf(stderr, "       ⏩ %lu\n", etor->obj.nWords * (sizeof(word_t)));
    END

    TEST(evaluator_checkBindAndLookup)
        struct Identifier* a = identifier_new("a");
        struct Identifier* b = identifier_new("b");
        struct Identifier* c = identifier_new("c");
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        struct Evaluator* etor = evaluator_new();
        evaluator_bind(etor, a, OBJ(i100));
        evaluator_bind(etor, b, OBJ(i200));
        struct Object* value;
        ASSERT_TRUE(evaluator_lookup(etor, a, &value));
        EXPECT_EQ(i100, value);
        ASSERT_TRUE(evaluator_lookup(etor, b, &value));
        EXPECT_EQ(i200, value);
        ASSERT_FALSE(evaluator_lookup(etor, c, &value));
    END

    END_TESTS
}

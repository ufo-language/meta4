#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(etor_rec_checkConstruction)
        struct Etor_Rec* etor = etor_rec_new();
        ASSERT_ISA(OT_Etor_Rec, etor);
    END

    TEST(etor_rec_showSize)
        struct Etor_Rec* etor = etor_rec_new();
        MESSAGE("Evaluator NWORDS:")
        fprintf(stderr, "       ⏩ %lu\n", etor->obj.nWords);
        MESSAGE("Evaluator NBYTES:")
        fprintf(stderr, "       ⏩ %lu\n", etor->obj.nWords * (sizeof(word_t)));
    END

    TEST(etor_rec_checkBindAndLookup)
        struct Identifier* a = identifier_new("a");
        struct Identifier* b = identifier_new("b");
        struct Identifier* c = identifier_new("c");
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        struct Etor_Rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        struct Object* value;
        ASSERT_TRUE(etor_rec_lookup(etor, a, &value));
        EXPECT_EQ(i100, value);
        ASSERT_TRUE(etor_rec_lookup(etor, b, &value));
        EXPECT_EQ(i200, value);
        ASSERT_FALSE(etor_rec_lookup(etor, c, &value));
    END

    END_TESTS
}

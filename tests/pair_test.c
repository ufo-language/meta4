#include "_test.h"
#include "_typedefs.h"

#include "object/functions/eval_rec.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/pair.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a = identifier_new("a");
    struct Identifier* b = identifier_new("b");
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(pair_checkConstruction)
        struct Pair* pair = pair_new(OBJ(i100), OBJ(i200));
        EXPECT_ISA(OT_Pair, pair);
        ASSERT_EQ(i100, pair->first);
        ASSERT_EQ(i200, pair->rest);
        EXPECT_IEQ(NWORDS(struct Object) + 2, pair->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Pair), pair->obj.nWords);
    END

    TEST(pair_checkEval)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        struct Pair* pair = pair_new(OBJ(a), OBJ(b));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(pair), etor, &value));
        ASSERT_ISA(OT_Pair, value);
        EXPECT_EQ(i100, ((struct Pair*)value)->first);
        EXPECT_EQ(i200, ((struct Pair*)value)->rest);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/globals.h"
#include "object/types/boolean.h"
#include "object/types/ifthen.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(ifThen_checkConstruction)
        struct IfThen* ifThen = ifThen_new(OBJ(g_true), OBJ(i100), OBJ(i200));
        ASSERT_ISA(OT_IfThen, ifThen);
        EXPECT_EQ(OBJ(g_true), ifThen->cond);
        EXPECT_EQ(OBJ(i100), ifThen->conseq);
        EXPECT_EQ(OBJ(i200), ifThen->alt);
        EXPECT_IEQ(NWORDS(struct Object) + 3, ifThen->obj.nWords);
        EXPECT_IEQ(NWORDS(struct IfThen), ifThen->obj.nWords);
    END

    TEST(ifThen_checkEval_true)
        struct IfThen* ifThen = ifThen_new(OBJ(g_true), OBJ(i100), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(ifThen), etor, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(ifThen_checkEval_false)
        struct IfThen* ifThen = ifThen_new(OBJ(g_false), OBJ(i100), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(ifThen), etor, &value));
        EXPECT_EQ(i200, value);
    END

    END_TESTS
}

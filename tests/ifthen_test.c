#include "_test.h"
#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/boolean.h"
#include "object/types/evaluator.h"
#include "object/types/ifthen.h"
#include "object/types/integer.h"
#include "object/types/evaluator.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(ifThen_checkConstruction)
        struct IfThen* ifThen = ifThen_new(OBJ(g_true), OBJ(i100), OBJ(i200));
        ASSERT_IEQ(OT_IfThen, ifThen->obj.typeId);
        EXPECT_EQ(OBJ(g_true), ifThen->cond);
        EXPECT_EQ(OBJ(i100), ifThen->conseq);
        EXPECT_EQ(OBJ(i200), ifThen->alt);
    END

    TEST(ifThen_checkEval_true)
        struct IfThen* ifThen = ifThen_new(OBJ(g_true), OBJ(i100), OBJ(i200));
        struct Evaluator* etor = etor_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(ifThen), etor, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(ifThen_checkEval_false)
        struct IfThen* ifThen = ifThen_new(OBJ(g_false), OBJ(i100), OBJ(i200));
        struct Evaluator* etor = etor_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(ifThen), etor, &value));
        EXPECT_EQ(i200, value);
    END

    END_TESTS
}

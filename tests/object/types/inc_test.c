#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/inc.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);

    TEST(inc_checkConstruction)
        struct Inc* inc = inc_new(OBJ(i100));
        ASSERT_ISA(OT_Inc, inc);
        EXPECT_EQ(i100, inc->expr);
        EXPECT_IEQ(NWORDS(struct Object) + 1, inc->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Inc), inc->obj.nWords);
    END

    TEST(inc_checkEval_integer)
        struct Inc* inc = inc_new(OBJ(i100));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(inc), etor, &value));
        ASSERT_ISA(OT_Integer, value);
        EXPECT_IEQ(101, ((struct Integer*)value)->i);
    END

    TEST(inc_checkEval_intVar)
        struct IntVar* iv100 = intVar_new(100);
        struct Inc* inc = inc_new(OBJ(iv100));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(inc), etor, &value));
        ASSERT_EQ(iv100, value);
        EXPECT_IEQ(101, ((struct IntVar*)value)->i);
    END

    TEST(inc_checkShow)
        struct Inc* inc = inc_new(OBJ(i100));
        EXPECT_SHOW("Inc{100}", inc);
    END

    END_TESTS
}

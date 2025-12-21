#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/dec.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);

    TEST(dec_checkConstruction)
        struct Dec* dec = dec_new(OBJ(i100));
        ASSERT_ISA(OT_Dec, dec);
        EXPECT_EQ(i100, dec->expr);
        EXPECT_IEQ(NWORDS(struct Object) + 1, dec->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Dec), dec->obj.nWords);
    END

    TEST(dec_checkEval_integer)
        struct Dec* dec = dec_new(OBJ(i100));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(dec), etor, &value));
        ASSERT_ISA(OT_Integer, value);
        EXPECT_IEQ(99, ((struct Integer*)value)->i);
    END

    TEST(dec_checkEval_intVar)
        struct IntVar* iv100 = intVar_new(100);
        struct Dec* dec = dec_new(OBJ(iv100));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(dec), etor, &value));
        ASSERT_EQ(iv100, value);
        EXPECT_IEQ(99, ((struct IntVar*)value)->i);
    END

    TEST(inc_checkShow)
        struct Dec* dec = dec_new(OBJ(i100));
        SHOW("Show show 'Dec(100)'", dec);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/sequence.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);
    struct Integer* i300 = integer_new(200);
    struct Object* exprs[] = {OBJ(i100), OBJ(i200), OBJ(i300)};

    TEST(sequence_checkConstruction)
        struct Sequence* seq = sequence_new(3, exprs);
        ASSERT_ISA(OT_Sequence, seq);
        ASSERT_IEQ(3, seq->nExprs);
        EXPECT_EQ(i100, seq->exprs[0]);
        EXPECT_EQ(i200, seq->exprs[1]);
        EXPECT_EQ(i300, seq->exprs[2]);
    END

    TEST(sequence_checkEval)
        struct Symbolic* a = identifier_new("a");
        struct Symbolic* b = identifier_new("b");
        struct Symbolic* c = identifier_new("c");
        struct Object* identExprs[] = {OBJ(a), OBJ(b), OBJ(c)};
        struct Sequence* seq = sequence_new(3, identExprs);
        struct Etor_Rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        etor_rec_bind(etor, c, OBJ(i300));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(seq), etor, &value));
        EXPECT_EQ(i300, value);
    END

    TEST(sequence_checkShow)
        struct Sequence* seq = sequence_new(3, exprs);
        SHOW("Should show '(100; 200; 300)'", seq);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/types/evaluator.h"
#include "object/types/integer.h"
#include "object/types/sequence.h"
#include "object/functions/eval.h"
#include "object/functions/show.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);
    struct Object* exprs[] = {OBJ(i100), OBJ(i200)};

    TEST(sequence_checkConstruction)
        struct Sequence* seq = sequence_new(2, exprs);
        ASSERT_IEQ(OT_Sequence, seq->obj.typeId);
        ASSERT_IEQ(2, seq->nExprs);
        EXPECT_EQ(i100, seq->exprs[0]);
        EXPECT_EQ(i200, seq->exprs[1]);
    END

    TEST(sequence_checKEval)
        struct Sequence* seq = sequence_new(2, exprs);
        struct Evaluator* etor = evaluator_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(seq), etor, &value));
    END

    TEST(sequence_checkShow)
        struct Sequence* seq = sequence_new(2, exprs);
        SHOW("Should show '(100; 200)'", seq);
    END

    END_TESTS
}

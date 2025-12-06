#include "_test.h"
#include "_typedefs.h"

#include "object/functions/eval.h"
#include "object/functions/show.h"
#include "object/types/evaluator.h"
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
        ASSERT_IEQ(OT_Sequence, seq->obj.typeId);
        ASSERT_IEQ(3, seq->nExprs);
        EXPECT_EQ(i100, seq->exprs[0]);
        EXPECT_EQ(i200, seq->exprs[1]);
        EXPECT_EQ(i300, seq->exprs[2]);
    END

    TEST(sequence_checkEval)
        struct Identifier* a = identifier_new("a");
        struct Identifier* b = identifier_new("b");
        struct Identifier* c = identifier_new("c");
        struct Object* identExprs[] = {OBJ(a), OBJ(b), OBJ(c)};
        struct Sequence* seq = sequence_new(3, identExprs);
        struct Evaluator* etor = evaluator_new();
        evaluator_bind(etor, a, OBJ(i100));
        evaluator_bind(etor, b, OBJ(i200));
        evaluator_bind(etor, c, OBJ(i300));
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(seq), etor, &value));
        EXPECT_EQ(i300, value);
    END

    TEST(sequence_checkShow)
        struct Sequence* seq = sequence_new(3, exprs);
        SHOW("Should show '(100; 200; 300)'", seq);
    END

    END_TESTS
}

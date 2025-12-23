#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/globals.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/let.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a = identifier_new("a");
    struct Identifier* b = identifier_new("b");
    struct Integer* i100 = integer_new(100);

    TEST(let_checkConstruction)
        struct Let* let = let_new(OBJ(a), OBJ(i100));
        ASSERT_ISA(OT_Let, let);
        ASSERT_IEQ(NWORDS(struct Let), let->obj.nWords);
        EXPECT_EQ(a, let->lhs);
        EXPECT_EQ(i100, let->rhs);
    END

    TEST(let_checkClose)
        struct Let* let = let_new(OBJ(a), OBJ(b));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, b, OBJ(i100));
        struct Object* value = close_rec(OBJ(let), etor);
        ASSERT_ISA(OT_Let, value);
        struct Let* closedLet = (struct Let*)value;
        EXPECT_EQ(i100, closedLet->rhs);
    END

    TEST(let_checkEval)
        struct Let* let = let_new(OBJ(a), OBJ(i100));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(let), etor, &value));
        EXPECT_EQ(g_nil, value);
        EXPECT_TRUE(etor_rec_lookup(etor, a, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(let_checkShow)
        struct Let* let = let_new(OBJ(a), OBJ(i100));
        EXPECT_SHOW("let a = 100", let);
    END

    END_TESTS
}

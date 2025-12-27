#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/types/binop.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(prim_binOp_checkConstruction)
        struct Object* lhs = OBJ(identifier_new("x"));
        struct Object* oper = OBJ(identifier_new(":="));
        struct BinOp* binOp = binOp_new(lhs, oper, OBJ(i100));
        ASSERT_ISA(OT_BinOp, binOp);
        ASSERT_IEQ(NWORDS(struct Object) + 4, binOp->obj.nWords);
        ASSERT_IEQ(NWORDS(struct BinOp), binOp->obj.nWords);
        EXPECT_EQ(lhs, binOp->lhs);
        EXPECT_EQ(oper, binOp->oper);
        EXPECT_EQ(i100, binOp->rhs);
        EXPECT_ISA(OT_Application, binOp->application);
    END

    TEST(prim_binOp_checkAssign)
        struct Identifier* x = identifier_new("x");
        struct Identifier* assign = identifier_new(":=");
        struct BinOp* binOp = binOp_new(OBJ(x), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i100));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
    END

    END_TESTS
}

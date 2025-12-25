#include "_test.h"
#include "_typedefs.h"

#include "object/types/application.h"
#include "object/types/binop.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* plus = identifier_new("+");
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(binOp_checkConstruction)
        struct BinOp* binOp = binOp_new(OBJ(i100), OBJ(plus), OBJ(i200));
        ASSERT_ISA(OT_BinOp, binOp);
        ASSERT_IEQ(NWORDS(struct Object) + 4, binOp->obj.nWords);
        ASSERT_IEQ(NWORDS(struct BinOp), binOp->obj.nWords);
        ASSERT_EQ(i100, binOp->lhs);
        ASSERT_EQ(plus, binOp->oper);
        ASSERT_EQ(i200, binOp->rhs);
        ASSERT_ISA(OT_Application, binOp->application);
        struct Application* app = binOp->application;
        ASSERT_EQ(binOp->oper, app->abstraction);
        ASSERT_IEQ(2, app->nArgs);
        ASSERT_EQ(i100, app->args[0]);
        ASSERT_EQ(i200, app->args[1]);
    END

    TEST(binOp_checkShow)
        struct BinOp* binOp = binOp_new(OBJ(i100), OBJ(plus), OBJ(i200));
        EXPECT_SHOW("100 + 200", binOp);
    END

    END_TESTS
}

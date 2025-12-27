#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/binop.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/subscript.h"
#include "object/types/variable.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a = identifier_new("a");
    struct Identifier* assign = identifier_new(":=");
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(prim_binOp_checkConstruction)
        struct Object* lhs = OBJ(a);
        struct Object* oper = OBJ(assign);
        struct Object* rhs = OBJ(i100);
        struct BinOp* binOp = binOp_new(lhs, oper, rhs);
        ASSERT_ISA(OT_BinOp, binOp);
        ASSERT_IEQ(NWORDS(struct Object) + 4, binOp->obj.nWords);
        ASSERT_IEQ(NWORDS(struct BinOp), binOp->obj.nWords);
        EXPECT_EQ(lhs, binOp->lhs);
        EXPECT_EQ(oper, binOp->oper);
        EXPECT_EQ(i100, binOp->rhs);
        EXPECT_ISA(OT_Application, binOp->application);
    END

    TEST(prim_binOp_checkAssign_identifier)
        struct BinOp* binOp = binOp_new(OBJ(a), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_TRUE(etor_rec_lookup(etor, a, &value));
        EXPECT_EQ(i200, value);
    END

    TEST(prim_binOp_checkAssign_subscript)
        struct Identifier* a = identifier_new("a");
        struct Integer* i0 = integer_new(0);
        struct Object* base = OBJ(a);
        struct Object* index = OBJ(i0);
        struct Subscript* subs = subscript_new(base, index);
        struct Array* array = array_new_withElem(1, OBJ(i100));
        struct BinOp* binOp = binOp_new(OBJ(subs), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(array));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_EQ(i200, array->elems[0]);
    END

    TEST(prim_binOp_checkAssign_variable)
        struct Identifier* a = identifier_new("a");
        struct Variable* var = variable_new(OBJ(g_nil));
        struct BinOp* binOp = binOp_new(OBJ(var), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(var));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_EQ(i200, var->value);
        SHOW("var", var);
    END

    END_TESTS
}

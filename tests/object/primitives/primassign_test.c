#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/binop.h"
#include "object/types/hashtable.h"
#include "object/types/identifier.h"
#include "object/types/intarray.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/intvector.h"
#include "object/types/subscript.h"
#include "object/types/symbol.h"
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

    TEST(prim_binOp_checkAssign_variable)
        struct Variable* var = variable_new(OBJ(g_nil));
        struct BinOp* binOp = binOp_new(OBJ(var), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(var));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_EQ(i200, var->value);
    END

    TEST(prim_binOp_checkAssign_intVar)
        struct IntVar* intVar = intVar_new(0);
        struct BinOp* binOp = binOp_new(OBJ(intVar), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(intVar));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_IEQ(200, intVar->i);
    END

    TEST(prim_binOp_checkAssign_subscript_array)
        struct Integer* i0 = integer_new(0);
        struct Object* base = OBJ(a);
        struct Object* index = OBJ(i0);
        struct Subscript* subs = subscript_new(base, index);
        struct BinOp* binOp = binOp_new(OBJ(subs), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        struct Array* array = array_new_withElem(1, OBJ(i100));
        etor_rec_bind(etor, a, OBJ(array));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_EQ(i200, array->elems[0]);
    END

    TEST(prim_binOp_checkAssign_subscript_hashTable)
        struct Identifier* h = identifier_new("h");
        struct Symbol* x = symbol_new("X");
        struct Object* base = OBJ(h);
        struct Object* index = OBJ(x);
        struct Subscript* subs = subscript_new(base, index);
        struct BinOp* binOp = binOp_new(OBJ(subs), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        struct HashTable* hashTable = hashTable_new();
        etor_rec_bind(etor, h, OBJ(hashTable));
        struct Object* value;
        EXPECT_SHOW("h[X] := 200", binOp);
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_IEQ(SubscriptResult_OK, hashTable_get(hashTable, OBJ(x), &value));
        EXPECT_EQ(i200, value);
    END

    TEST(prim_binOp_checkAssign_subscript_intArray)
        struct Identifier* ia = identifier_new("ia");
        struct Integer* i0 = integer_new(0);
        struct Object* base = OBJ(ia);
        struct Object* index = OBJ(i0);
        struct Subscript* subs = subscript_new(base, index);
        struct BinOp* binOp = binOp_new(OBJ(subs), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        struct IntArray* intArray = intArray_new_elem(1, 0);
        etor_rec_bind(etor, ia, OBJ(intArray));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_IEQ(200, intArray->elems[0]);
    END

    TEST(prim_binOp_checkAssign_subscript_intVector)
        struct Identifier* iv = identifier_new("iv");
        struct Integer* i0 = integer_new(0);
        struct Object* base = OBJ(iv);
        struct Object* index = OBJ(i0);
        struct Subscript* subs = subscript_new(base, index);
        struct BinOp* binOp = binOp_new(OBJ(subs), OBJ(assign), OBJ(i200));
        struct Etor_rec* etor = etor_rec_new();
        struct IntVector* intVector = intVector_new();
        intVector_push(intVector, 100);
        etor_rec_bind(etor, iv, OBJ(intVector));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(binOp), etor, &value));
        EXPECT_EQ(i200, value);
        EXPECT_IEQ(200, intVector->elems->elems[0]);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/apply.h"
#include "object/globals.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/primitive.h"

count_t testFunction1CallCount = 0;
count_t testFunction2CallCount = 0;

bool_t testFunction1(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    (void)args;
    (void)value;
    ++testFunction1CallCount;
    return true;
}

bool_t testFunction2(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    (void)args;
    (void)value;
    ++testFunction2CallCount;
    return true;
}

bool_t testFunction3(struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    (void)etor;
    (void)nArgs;
    (void)args;
    (void)value;
    *value = args[0];
    return true;
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* foo = identifier_new("foo");
    struct Integer* i100 = integer_new(100);

    TEST(primitive_checkConstruction)
        struct Primitive* prim = prim_newFunction("foo");
        ASSERT_ISA(OT_Primitive, prim);
        ASSERT_IEQ(NWORDS(struct Primitive), prim->obj.nWords);
        EXPECT_EQ(foo, prim->name);
        EXPECT_EQ(g_emptyPrimRule, prim->rules);
    END

    TEST(primitive_checkApply_1rule0params)
        struct Primitive* prim = prim_newFunction("foo");
        prim_addRule(prim, testFunction1, 0);
        struct Etor_rec* etor = etor_rec_new();
        count_t nArgs = 0;
        struct Object* args[] = {OBJ(g_nil)};  /* Compiler wants at least one value in any array */
        struct Object* value;
        testFunction1CallCount = 0;
        testFunction2CallCount = 0;
        ASSERT_TRUE(apply((struct Object*)prim, etor, nArgs, args, &value));
        EXPECT_IEQ(1, testFunction1CallCount);
        EXPECT_IEQ(0, testFunction2CallCount);
    END

    TEST(primitive_checkApply_1rule1param)
        struct Primitive* prim = prim_newFunction("foo");
        prim_addRule(prim, testFunction1, 1, OT_Integer);
        struct Etor_rec* etor = etor_rec_new();
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(i100)};
        struct Object* value;
        testFunction1CallCount = 0;
        testFunction2CallCount = 0;
        ASSERT_TRUE(apply(OBJ(prim), etor, nArgs, args, &value));
        EXPECT_IEQ(1, testFunction1CallCount);
        EXPECT_IEQ(0, testFunction2CallCount);
    END

    TEST(primitive_checkApply_2rules1param)
        struct Primitive* prim = prim_newFunction("foo");
        prim_addRule(prim, testFunction1, 1, OT_Integer);
        prim_addRule(prim, testFunction2, 1, OT_Boolean);
        struct Etor_rec* etor = etor_rec_new();
        count_t nArgs = 1;
        struct Object* args1[] = {OBJ(i100)};
        struct Object* value;
        testFunction1CallCount = 0;
        testFunction2CallCount = 0;
        ASSERT_TRUE(apply(OBJ(prim), etor, nArgs, args1, &value));
        EXPECT_IEQ(1, testFunction1CallCount);
        EXPECT_IEQ(0, testFunction2CallCount);
        struct Object* args2[] = {OBJ(g_true)};
        testFunction1CallCount = 0;
        testFunction2CallCount = 0;
        ASSERT_TRUE(apply(OBJ(prim), etor, nArgs, args2, &value));
        EXPECT_IEQ(0, testFunction1CallCount);
        EXPECT_IEQ(1, testFunction2CallCount);
    END

    TEST(primitive_checkApply_macro)
        struct Primitive* prim = prim_newMacro("foo");
        prim_addRule(prim, testFunction3, 1, OT_Any);
        struct Etor_rec* etor = etor_rec_new();
        struct Identifier* x = identifier_new("x");
        count_t nArgs = 1;
        struct Object* args1[] = {OBJ(x)};
        struct Object* value;
        ASSERT_TRUE(apply(OBJ(prim), etor, nArgs, args1, &value));
        EXPECT_EQ(x, value);
    END

    TEST(primitive_show)
        struct Primitive* prim = prim_newFunction("foo");
        EXPECT_SHOW("@foo", prim);
    END

    END_TESTS
}

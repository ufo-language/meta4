#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* f = identifier_new("f");
    struct Identifier* x = identifier_new("x");
    struct Identifier* y = identifier_new("y");

    TEST(function_checkConstruction)
        count_t nParams = 2;
        struct Object* params[] = {OBJ(x), OBJ(y)};
        struct Object* body = OBJ(g_nil);
        struct Function* function = function_new(f, nParams, params, body, g_emptyFunctionRule);
        ASSERT_ISA(OT_Function, function);
        EXPECT_IEQ(NWORDS(struct Object) + 3 + nParams, function->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Function) + nParams, function->obj.nWords);
    END

    TEST(function_checkShow)
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(y);
        struct Function* function = function_new(f, nParams, params, body, g_emptyFunctionRule);
        SHOW("Function", function);
    END

    TEST(function_checkClose)
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(y);
        struct Etor_rec* etor = etor_rec_new();
        struct Function* function = function_new(f, nParams, params, body, g_emptyFunctionRule);
        SHOW("Function 1", function);
        ASSERT_EQ(g_emptyFunctionRule, function->closedRules);
        SHOW("Function 2", function);
        struct Integer* i100 = integer_new(100);
        SHOW("Function 3", function);
        etor_rec_bind(etor, y, OBJ(i100));
        SHOW("Function 4", function);
        struct Object* value;
        ASSERT_TRUE(function_close_rec(function, etor, &value));
        ASSERT_EQ(function, value);
        EXPECT_EQ(i100, function->closedRules->body);
    END

    END_TESTS
}

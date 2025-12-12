#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/application.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* f = identifier_new("f");
    struct Identifier* x = identifier_new("x");
    struct Identifier* y = identifier_new("y");
    struct Integer* i100 = integer_new(100);

    TEST(function_checkConstruction_0rules)
        struct Function* function = function_new(f);
        ASSERT_ISA(OT_Function, function);
        EXPECT_IEQ(NWORDS(struct Object) + 2, function->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Function), function->obj.nWords);
        ASSERT_PTREQ(g_emptyFunctionRule, function->rules);
    END

    TEST(function_checkConstruction_1rule)
        struct Function* function = function_new(f);
        count_t nParams = 2;
        struct Object* params[] = {OBJ(x), OBJ(y)};
        struct Object* body = OBJ(g_nil);
        function_addlRule(function, nParams, params, body);
        ASSERT_PTRNE(g_emptyFunctionRule, function->rules);
    END

    TEST(function_checkShow_1Rule)
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(y);
        function_addlRule(function, nParams, params, body);
        SHOW("Should show 'fun f(x) = x'", function);
    END

    TEST(function_checkClose_1rule)
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(y);
        struct Etor_rec* etor = etor_rec_new();
        function_addlRule(function, nParams, params, body);
        etor_rec_bind(etor, y, OBJ(i100));
        struct Object* value = function_close_rec(function, etor);
        ASSERT_EQ(function, value);
        EXPECT_EQ(y, function->rules->body);
        EXPECT_EQ(i100, function->rules->closedBody);
    END

    TEST(function_checkApply_1rule)
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(x);
        struct Etor_rec* etor = etor_rec_new();
        function_addlRule(function, nParams, params, body);
        struct Object* value = function_close_rec(function, etor);
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(i100)};
        ASSERT_TRUE(function_apply(function, etor, nArgs, args, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(function_checkApplicationEvalWithFunction)
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(x);
        struct Etor_rec* etor = etor_rec_new();
        function_addlRule(function, nParams, params, body);
        struct Object* value = function_close_rec(function, etor);
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(i100)};
        struct Application* app = application_new(OBJ(function), nArgs, args);
        ASSERT_TRUE(eval_rec(OBJ(app), etor, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(function_checkShow_2Rules)
        struct Function* function = function_new(f);
        count_t nParams = 2;
        struct Object* params[] = {OBJ(x), OBJ(y)};
        struct Object* body = OBJ(x);
        function_addlRule(function, nParams, params, body);
        nParams = 1;
        struct Object* params1[] = {OBJ(x)};
        body = OBJ(x);
        function_addlRule(function, nParams, params1, body);
        SHOW("Should show 'fun f(x, y) = y | b(x) = x'", function);
    END

    END_TESTS
}

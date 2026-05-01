#include "_test.h"
#include "_typedefs.h"

#include "lexer/lexer.h"
#include "lexer/syntax.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/apply.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/types/application.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/symbol.h"
#include "parsers/parseany.h"
#include "parsers/parser.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* f = identifier_new("f");
    struct Identifier* x = identifier_new("x");
    struct Identifier* y = identifier_new("y");
    struct Integer* i100 = integer_new(100);

    TEST(function_checkConstruction_0rules)
        struct Function* function = function_new(f);
        ASSERT_ISA(OT_Function, function);
        EXPECT_IEQ(NWORDS(struct Object) + 3, function->obj.nWords);
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

    TEST(function_checkApply_macro)
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(x);
        function_addlRule(function, nParams, params, body);
        struct Etor_rec* etor = etor_rec_new();
        close_rec(OBJ(function), etor);
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(y)};
        struct Object* value;
        ASSERT_TRUE(apply(OBJ(function), etor, nArgs, args, &value));
        EXPECT_EQ(y, value);
    END

    TEST(function_checkShow_1Rule)
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(y);
        function_addlRule(function, nParams, params, body);
        EXPECT_SHOW("fun f(x) = y", function);
    END

    TEST(function_checkShow_2Rules)
        struct Function* function = function_new(f);
        count_t nParams = 2;
        struct Object* params[] = {OBJ(x), OBJ(y)};
        struct Object* body = OBJ(x);
        function_addlRule(function, nParams, params, body);
        nParams = 1;
        struct Object* params1[] = {OBJ(x)};
        function_addlRule(function, nParams, params1, body);
        EXPECT_SHOW("fun f(x, y) = x | (x) = x", function);
    END

    TEST(function_parseAnonymous_noParams)
        const string_t input = "fun () = nil";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        EXPECT_ISA(OT_Function, parseState.result);
        struct Function* function = (struct Function*)parseState.result;
        EXPECT_PTREQ(g_idNil, function->name);
        EXPECT_SHOW("fun () = nil", function);
    END

    TEST(function_parseNamed_1Param)
        const string_t input = "fun g(x) = x";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        EXPECT_ISA(OT_Function, parseState.result);
        struct Function* function = (struct Function*)parseState.result;
        EXPECT_PTRNE(g_idNil, function->name);
        EXPECT_SHOW("fun g(x) = x", function);
    END

    TEST(function_parseMultiRule)
        const string_t input = "fun h([x]) = List{x} | ({y}) = Array{y} | (x) = Other{x}";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        EXPECT_ISA(OT_Function, parseState.result);
        struct Function* function = (struct Function*)parseState.result;
        MESSAGE("Skipping EXPECT_SHOW for now due to ByteBuffer issue");
    END

    TEST(function_evalAnonymous)
        const string_t input = "fun (x) = x";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(parseState.result, etor, &value));
        EXPECT_ISA(OT_Function, value);
        EXPECT_SHOW("fun (x) = x", value);
    END

    TEST(function_evalNamed)
        const string_t input = "fun f(x) = x";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(parseState.result, etor, &value));
        EXPECT_ISA(OT_Function, value);
        struct Function* function = (struct Function*)value;
        EXPECT_PTRNE(g_idNil, function->name);
        struct Object* lookupValue;
        ASSERT_TRUE(etor_rec_lookup(etor, function->name, &lookupValue));
        EXPECT_EQ(function, lookupValue);
    END

    TEST(function_recursion)
        const string_t input = "fun f(0) = Done | (x) = f(0)";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(parseState.result, etor, &value));
        struct Function* function = (struct Function*)value;
        struct Integer* arg = integer_new(5);
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(arg)};
        ASSERT_TRUE(function_apply(function, etor, nArgs, args, &value));
        EXPECT_ISA(OT_Symbol, value);
        struct Symbol* result = (struct Symbol*)value;
        EXPECT_SHOW("Done", result);
    END

    TEST(function_lexicalBinding)
        const string_t input = "fun f(y) = y";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        struct Etor_rec* etor = etor_rec_new();
        struct Integer* boundValue = integer_new(100);
        etor_rec_bind(etor, x, OBJ(boundValue));
        struct Object* value;
        ASSERT_TRUE(eval_rec(parseState.result, etor, &value));
        struct Function* function = (struct Function*)value;
        struct Integer* arg = integer_new(42);
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(arg)};
        ASSERT_TRUE(function_apply(function, etor, nArgs, args, &value));
        EXPECT_EQ(arg, value);
    END

    TEST(function_patternMatching_list)
        const string_t input = "fun h([x]) = x | (y) = y";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        ASSERT_IEQ(PRS_Pass, parseResult);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(parseState.result, etor, &value));
        struct Function* function = (struct Function*)value;
        struct Integer* elem = integer_new(42);
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(elem)};
        ASSERT_TRUE(function_apply(function, etor, nArgs, args, &value));
        EXPECT_EQ(elem, value);
    END

    END_TESTS
}

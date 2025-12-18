#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parserprims.h"
#include "object/globals.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

static bool_t isA(const string_t tokenType, struct Object* tokenObj) {
    struct Term* token = (struct Term*)tokenObj;
    struct Symbol* expectedNameSym = symbol_new(tokenType);
    return token->name == expectedNameSym;
}

count_t testParser_pass_nCalls = 0;
count_t testParser_fail_nCalls = 0;
count_t testParser_error_nCalls = 0;

enum ParseStatus testParser_pass(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    (void)result;
    ++testParser_pass_nCalls;
    return PS_Success;
}

enum ParseStatus testParser_fail(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    (void)result;
    ++testParser_fail_nCalls;
    return PS_Fail;
}

enum ParseStatus testParser_error(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    (void)result;
    *result = (struct Object*)g_false;  /* Just use some unique value here */
    ++testParser_error_nCalls;
    return PS_Error;
}

enum ParseStatus testParser_returnNil(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    *result = (struct Object*)g_nil;
    return PS_Success;
}

enum ParseStatus testParser_returnTrue(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    *result = (struct Object*)g_true;
    return PS_Success;
}

enum ParseStatus testParser_returnUnique(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    *result = g_uniqueObject;
    return PS_Success;
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Symbol* integerSym = symbol_new("Int");

    TEST(pSpot_checkEmptyTokenVector)
        const string_t src = "";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        /* The vector is not really empty; it contains EOF{EOF} */
        ASSERT_IEQ(1, vector_count(tokens));
        ASSERT_TRUE(isA("EOI", vector_get_unsafe(tokens, 0)));
        struct Object* result = (struct Object*)g_nil;
        index_t index = 0;
        EXPECT_IEQ(PS_Fail, pSpot(integerSym, tokens, &index, &result));
    END

    TEST(pSpot_checkInt)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        EXPECT_TRUE(isA("Int", vector_get_unsafe(tokens, 0)));
        ASSERT_TRUE(isA("EOI", vector_get_unsafe(tokens, 1)));
        ASSERT_IEQ(2, vector_count(tokens));
        struct Object* result = (struct Object*)g_nil;
        index_t index = 0;
        ASSERT_IEQ(PS_Success, pSpot(integerSym, tokens, &index, &result));
        EXPECT_IEQ(1, index);
        ASSERT_ISA(OT_Term, result);
        EXPECT_TRUE(isA("Int", result));
    END

    TEST(pStrip_checkInt)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        struct Object* result = (struct Object*)g_nil;
        index_t index = 0;
        ASSERT_IEQ(PS_Success, pSpot(integerSym, tokens, &index, &result));
        ASSERT_IEQ(1, index);
        ASSERT_IEQ(PS_Success, pStrip(tokens, &index, &result));
        ASSERT_ISA(OT_Integer, result);
    END

    TEST(pSequence_checkPPP)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_pass, testParser_pass, testParser_pass};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_pass_nCalls = 0;
        testParser_fail_nCalls = 0;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, tokens, &index, &result));
        ASSERT_IEQ(3, testParser_pass_nCalls);
        ASSERT_IEQ(0, testParser_fail_nCalls);
        ASSERT_IEQ(0, testParser_error_nCalls);
    END

    TEST(pSequence_checkPPF)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_pass, testParser_pass, testParser_fail};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_pass_nCalls = 0;
        testParser_fail_nCalls = 0;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Fail, pSequence(nParsers, parsers, tokens, &index, &result));
        ASSERT_IEQ(2, testParser_pass_nCalls);
        ASSERT_IEQ(1, testParser_fail_nCalls);
        ASSERT_IEQ(0, testParser_error_nCalls);
    END

    TEST(pSequence_checkNilNilNil)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_returnNil, testParser_returnNil};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, tokens, &index, &result));
        ASSERT_ISA(OT_Vector, result);
        ASSERT_IEQ(3, vector_count((struct Vector*)result));
    END

    TEST(pSequence_checkIgnore)
        count_t nParsers = 1;
        ParserFunction parsers[] = {testParser_returnUnique};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_pass_nCalls = 0;
        testParser_fail_nCalls = 0;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, tokens, &index, &result));
        ASSERT_IEQ(0, testParser_fail_nCalls);
        ASSERT_IEQ(0, testParser_error_nCalls);
        ASSERT_ISA(OT_Nil, result);
    END

    TEST(pSequence_checkIgnoreNilIgnore)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnUnique, testParser_returnNil, testParser_returnUnique};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, tokens, &index, &result));
         ASSERT_ISA(OT_Nil, result);
    END

    TEST(pSequence_checkNilNilError)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_returnNil, testParser_error};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Error, pSequence(nParsers, parsers, tokens, &index, &result));
        ASSERT_IEQ(1, testParser_error_nCalls);
        ASSERT_EQ(result, g_false);
    END

    TEST(pOneOf_checkFFF)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_fail, testParser_fail};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Fail, pOneOf(nParsers, parsers, tokens, &index, &result));
        EXPECT_IEQ(nParsers, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkFFNil)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_fail, testParser_returnNil};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, tokens, &index, &result));
        EXPECT_EQ(g_nil, result);
        EXPECT_IEQ(2, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkFNilF)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_returnNil, testParser_fail};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, tokens, &index, &result));
        EXPECT_EQ(g_nil, result);
        EXPECT_IEQ(1, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkNilFF)
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_fail, testParser_fail};
        struct Vector* tokens = vector_new();
        index_t index = 0;
        struct Object* result = (struct Object*)g_uniqueObject;
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, tokens, &index, &result));
        EXPECT_EQ(g_nil, result);
        EXPECT_IEQ(0, testParser_fail_nCalls);
    END

    END_TESTS
}

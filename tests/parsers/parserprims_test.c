#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parserprims.h"
#include "parsers/parseliterals.h"
#include "parsers/parsespecialchars.h"
#include "parsers/parsereservedwords.h"
#include "object/globals.h"
#include "object/types/integer.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

static bool_t isA(struct Symbol* tokenType, struct Object* tokenObj) {
    struct Term* token = (struct Term*)tokenObj;
    return token->name == tokenType;
}

count_t testParser_pass_nCalls = 0;
count_t testParser_fail_nCalls = 0;
count_t testParser_error_nCalls = 0;

static enum ParseStatus testParser_pass(struct ParseState* parseState) {
    (void)parseState;
    ++testParser_pass_nCalls;
    return PS_Success;
}

static enum ParseStatus testParser_fail(struct ParseState* parseState) {
    (void)parseState;
    ++testParser_fail_nCalls;
    return PS_Fail;
}

static enum ParseStatus testParser_error(struct ParseState* parseState) {
    parseState->result = (struct Object*)g_false;  /* Just use some unique value here */
    ++testParser_error_nCalls;
    return PS_Error;
}

static enum ParseStatus testParser_returnNil(struct ParseState* parseState) {
    parseState->result = (struct Object*)g_nil;
    return PS_Success;
}

#if 0
static enum ParseStatus testParser_returnTrue(struct ParseState* parseState) {
    parseState->result = (struct Object*)g_true;
    return PS_Success;
}
#endif

static enum ParseStatus testParser_returnUnique(struct ParseState* parseState) {
    parseState->result = g_uniqueObject;
    return PS_Success;
}

static enum ParseStatus testParser_error1(struct ParseState* parseState) {
    return pError("error1", parseState);
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Vector* tokens = vector_new();

    TEST(pSpot_checkEmptyTokenVector)
        const string_t src = "";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        /* The vector is not really empty; it contains EOF{EOF} */
        ASSERT_IEQ(1, vector_count(parseState.tokens));
        ASSERT_TRUE(isA(g_symEOI, vector_get_unsafe(parseState.tokens, 0)));
        EXPECT_IEQ(PS_Fail, pSpot(g_symInteger, &parseState));
    END

    TEST(pSpot_checkInt)
        const string_t src = "123";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        EXPECT_TRUE(isA(g_symInteger, vector_get_unsafe(parseState.tokens, 0)));
        ASSERT_TRUE(isA(g_symEOI, vector_get_unsafe(parseState.tokens, 1)));
        ASSERT_IEQ(2, vector_count(parseState.tokens));
        ASSERT_IEQ(PS_Success, pSpot(g_symInteger, &parseState));
        EXPECT_IEQ(1, parseState.index);
        ASSERT_ISA(OT_Term, parseState.result);
        EXPECT_TRUE(isA(g_symInteger, parseState.result));
    END

    TEST(pStrip_checkInt)
        const string_t src = "123";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pSpot(g_symInteger, &parseState));
        ASSERT_IEQ(1, parseState.index);
        ASSERT_IEQ(PS_Success, pStrip(&parseState));
        ASSERT_ISA(OT_Integer, parseState.result);
        EXPECT_IEQ(123, ((struct Integer*)parseState.result)->i);
        EXPECT_IEQ(123, ((struct Integer*)parseState.result)->i);
    END

    TEST(pSequence_checkPPP)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_pass, testParser_pass, testParser_pass};
        testParser_pass_nCalls = 0;
        testParser_fail_nCalls = 0;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, &parseState));
        ASSERT_IEQ(3, testParser_pass_nCalls);
        ASSERT_IEQ(0, testParser_fail_nCalls);
        ASSERT_IEQ(0, testParser_error_nCalls);
    END

    TEST(pSequence_checkPPF)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_pass, testParser_pass, testParser_fail};
        testParser_pass_nCalls = 0;
        testParser_fail_nCalls = 0;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Fail, pSequence(nParsers, parsers, &parseState));
        ASSERT_IEQ(2, testParser_pass_nCalls);
        ASSERT_IEQ(1, testParser_fail_nCalls);
        ASSERT_IEQ(0, testParser_error_nCalls);
    END

    TEST(pSequence_checkNilNilNil)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_returnNil, testParser_returnNil};
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, &parseState));
        ASSERT_ISA(OT_Vector, parseState.result);
        ASSERT_IEQ(3, vector_count((struct Vector*)parseState.result));
    END

    TEST(pSequence_checkIgnore)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 1;
        ParserFunction parsers[] = {testParser_returnUnique};
        testParser_pass_nCalls = 0;
        testParser_fail_nCalls = 0;
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, &parseState));
        ASSERT_IEQ(0, testParser_fail_nCalls);
        ASSERT_IEQ(0, testParser_error_nCalls);
        ASSERT_ISA(OT_Nil, parseState.result);
    END

    TEST(pSequence_checkIgnoreNilIgnore)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnUnique, testParser_returnNil, testParser_returnUnique};
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, &parseState));
        ASSERT_ISA(OT_Nil, parseState.result);
    END

    TEST(pSequence_checkNilNilError)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_returnNil, testParser_error};
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Error, pSequence(nParsers, parsers, &parseState));
        ASSERT_IEQ(1, testParser_error_nCalls);
        ASSERT_EQ(g_false, parseState.result);
    END

    TEST(pOneOf_checkFFF)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_fail, testParser_fail};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Fail, pOneOf(nParsers, parsers, &parseState));
        EXPECT_IEQ(nParsers, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkFFNil)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_fail, testParser_returnNil};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, &parseState));
        EXPECT_EQ(g_nil, parseState.result);
        EXPECT_IEQ(2, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkFNilF)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_returnNil, testParser_fail};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, &parseState));
        EXPECT_EQ(g_nil, parseState.result);
        EXPECT_IEQ(1, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkNilFF)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_fail, testParser_fail};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, &parseState));
        EXPECT_EQ(g_nil, parseState.result);
        EXPECT_IEQ(0, testParser_fail_nCalls);
    END

    TEST(pSepBy_intSymbol_0)
        const string_t src = "";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pSepBy(pInteger, pSymbol, 0, &parseState));
        ASSERT_ISA(OT_Vector, parseState.result);
        ASSERT_IEQ(0, vector_count((struct Vector*)parseState.result));
    END

    TEST(pSepBy_intSymbol_1)
        const string_t src = "123";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pSepBy(pInteger, pSymbol, 1, &parseState));
        ASSERT_ISA(OT_Vector, parseState.result);
        ASSERT_IEQ(1, vector_count((struct Vector*)parseState.result));
    END

    TEST(pSepBy_intSymbol_3)
        const string_t src = "123 A 456 B 789";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pSepBy(pInteger, pSymbol, 3, &parseState));
        ASSERT_ISA(OT_Vector, parseState.result);
        ASSERT_IEQ(3, vector_count((struct Vector*)parseState.result));
    END

    TEST(pSepBy_intSymbol_3_fail_2)
        const string_t src = "123 A 456";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Fail, pSepBy(pInteger, pSymbol, 3, &parseState));
    END

    TEST(pSepBy_intSymbol_error_Sym)
        const string_t src = "123 A B";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Error, pSepBy(pInteger, pSymbol, 3, &parseState));
    END

    TEST(pSepBy_intSymbol_Fail)
        const string_t src = "123 456";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Fail, pSepBy(pInteger, pSymbol, 3, &parseState));
    END

    TEST(pListOf_success_0elems)
        const string_t src = "A x";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pListOf(pSymbol, pBoolean, pInteger, pIdentifier, &parseState));
    END

    TEST(pListOf_success_1elem)
        const string_t src = "A true x";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pListOf(pSymbol, pBoolean, pInteger, pIdentifier, &parseState));
    END

    TEST(pListOf_success_3elems)
        const string_t src = "A true 0 false 1 true x";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pListOf(pSymbol, pBoolean, pInteger, pIdentifier, &parseState));
    END

    TEST(pSpotSpecialChar_success)
        const string_t src = "{";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pSpecialOpenBrace(&parseState));
    END

    TEST(pSpotSpecialChar_fail)
        const string_t src = "X";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Fail, pSpecialOpenBrace(&parseState));
    END

    TEST(pSpotReserved_success)
        const string_t src = "end";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pReservedEnd(&parseState));
    END

    TEST(pSpotReserved_fail)
        const string_t src = "123";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Fail, pReservedEnd(&parseState));
    END

    TEST(pError)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        const string_t message = "message";
        ASSERT_IEQ(PS_Error, pError(message, &parseState));
        ASSERT_ISA(OT_String, parseState.result);
        ASSERT_IEQ(CompareEqual, string_compare_chars(((struct String*)parseState.result)->chars, message));
    END

    TEST(pSequence_withError)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_pass, testParser_pass, testParser_error1};
        ASSERT_IEQ(PS_Error, pSequence(nParsers, parsers, &parseState));
    END

    TEST(pOneOf_withError)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_error1, testParser_pass};
        ASSERT_IEQ(PS_Error, pOneOf(nParsers, parsers, &parseState));
    END

    TEST(pDebug_pass)
        vector_clear(tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PS_Success, pDebug(testParser_pass, "debug test Pass", &parseState));
        ASSERT_IEQ(PS_Fail, pDebug(testParser_fail, "debug test Fail", &parseState));
        ASSERT_IEQ(PS_Error, pDebug(testParser_error, "debug test Error", &parseState));
    END

    END_TESTS
}

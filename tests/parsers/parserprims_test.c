#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parserprims.h"
#include "object/globals.h"
#include "object/types/integer.h"
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

enum ParseStatus testParser_pass(struct ParseState* parseState) {
    (void)parseState;
    ++testParser_pass_nCalls;
    return PS_Success;
}

enum ParseStatus testParser_fail(struct ParseState* parseState) {
    (void)parseState;
    ++testParser_fail_nCalls;
    return PS_Fail;
}

enum ParseStatus testParser_error(struct ParseState* parseState) {
    parseState->result = (struct Object*)g_false;  /* Just use some unique value here */
    ++testParser_error_nCalls;
    return PS_Error;
}

enum ParseStatus testParser_returnNil(struct ParseState* parseState) {
    parseState->result = (struct Object*)g_nil;
    return PS_Success;
}

enum ParseStatus testParser_returnTrue(struct ParseState* parseState) {
    parseState->result = (struct Object*)g_true;
    return PS_Success;
}

enum ParseStatus testParser_returnUnique(struct ParseState* parseState) {
    parseState->result = g_uniqueObject;
    return PS_Success;
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Symbol* integerSym = symbol_new("Int");
    struct Vector* tokens = vector_new();

    TEST(pSpot_checkEmptyTokenVector)
        const string_t src = "";
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = lexer_lexAll_withVector(syntax, src, tokens),
            .index = 0,
            .result = (struct Object*)g_nil
        };
        /* The vector is not really empty; it contains EOF{EOF} */
        ASSERT_IEQ(1, vector_count(parseState.tokens));
        ASSERT_TRUE(isA("EOI", vector_get_unsafe(parseState.tokens, 0)));
        EXPECT_IEQ(PS_Fail, pSpot(integerSym, &parseState));
    END

    TEST(pSpot_checkInt)
        const string_t src = "123";
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = lexer_lexAll_withVector(syntax, src, tokens),
            .index = 0,
            .result = (struct Object*)g_nil
        };
        EXPECT_TRUE(isA("Int", vector_get_unsafe(parseState.tokens, 0)));
        ASSERT_TRUE(isA("EOI", vector_get_unsafe(parseState.tokens, 1)));
        ASSERT_IEQ(2, vector_count(parseState.tokens));
        ASSERT_IEQ(PS_Success, pSpot(integerSym, &parseState));
        EXPECT_IEQ(1, parseState.index);
        ASSERT_ISA(OT_Term, parseState.result);
        EXPECT_TRUE(isA("Int", parseState.result));
    END

    TEST(pStrip_checkInt)
        const string_t src = "123";
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = lexer_lexAll_withVector(syntax, src, tokens),
            .index = 0,
            .result = (struct Object*)g_nil
        };
        ASSERT_IEQ(PS_Success, pSpot(integerSym, &parseState));
        ASSERT_IEQ(1, parseState.index);
        ASSERT_IEQ(PS_Success, pStrip(&parseState));
        ASSERT_ISA(OT_Integer, parseState.result);
        EXPECT_IEQ(123, ((struct Integer*)parseState.result)->i);
        EXPECT_IEQ(123, ((struct Integer*)parseState.result)->i);
    END

    TEST(pSequence_checkPPP)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = (struct Object*)g_nil
        };
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
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = (struct Object*)g_nil
        };
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
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_returnNil, testParser_returnNil};
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, &parseState));
        ASSERT_ISA(OT_Vector, parseState.result);
        ASSERT_IEQ(3, vector_count((struct Vector*)parseState.result));
    END

    TEST(pSequence_checkIgnore)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
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
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnUnique, testParser_returnNil, testParser_returnUnique};
        ASSERT_IEQ(PS_Success, pSequence(nParsers, parsers, &parseState));
        ASSERT_ISA(OT_Nil, parseState.result);
    END

    TEST(pSequence_checkNilNilError)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_returnNil, testParser_error};
        testParser_error_nCalls = 0;
        ASSERT_IEQ(PS_Error, pSequence(nParsers, parsers, &parseState));
        ASSERT_IEQ(1, testParser_error_nCalls);
        ASSERT_EQ(g_false, parseState.result);
    END

    TEST(pOneOf_checkFFF)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_fail, testParser_fail};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Fail, pOneOf(nParsers, parsers, &parseState));
        EXPECT_IEQ(nParsers, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkFFNil)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_fail, testParser_returnNil};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, &parseState));
        EXPECT_EQ(g_nil, parseState.result);
        EXPECT_IEQ(2, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkFNilF)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_fail, testParser_returnNil, testParser_fail};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, &parseState));
        EXPECT_EQ(g_nil, parseState.result);
        EXPECT_IEQ(1, testParser_fail_nCalls);
    END

    TEST(pOneOf_checkNilFF)
        vector_clear(tokens);
        struct ParseState parseState = {
            .tokens = tokens,
            .index = 0,
            .result = g_uniqueObject
        };
        count_t nParsers = 3;
        ParserFunction parsers[] = {testParser_returnNil, testParser_fail, testParser_fail};
        testParser_fail_nCalls = 0;
        ASSERT_IEQ(PS_Success, pOneOf(nParsers, parsers, &parseState));
        EXPECT_EQ(g_nil, parseState.result);
        EXPECT_IEQ(0, testParser_fail_nCalls);
    END

    END_TESTS
}

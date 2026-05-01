#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parsedatastructures.h"
#include "object/types/integer.h"
#include "object/types/pair.h"
#include "object/types/term.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Vector* tokens = vector_new();

    TEST(pArray_checkEmpty)
        const string_t src = "{}";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pArray(&parseState));
        ASSERT_ISA(OT_Array, parseState.result);
        struct Array* array = (struct Array*)parseState.result;
        ASSERT_IEQ(0, array->nElems);
    END

    TEST(pArray_check1Element)
        const string_t src = "{100}";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pArray(&parseState));
        ASSERT_ISA(OT_Array, parseState.result);
        struct Array* array = (struct Array*)parseState.result;
        ASSERT_IEQ(1, array->nElems);
        ASSERT_ISA(OT_Integer, array->elems[0]);
        EXPECT_IEQ(100, ((struct Integer*)array->elems[0])->i);
    END

    TEST(pArray_check2Elements)
        const string_t src = "{100, 200}";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pArray(&parseState));
        ASSERT_ISA(OT_Array, parseState.result);
        struct Array* array = (struct Array*)parseState.result;
        ASSERT_IEQ(2, array->nElems);
        ASSERT_ISA(OT_Integer, array->elems[0]);
        EXPECT_IEQ(100, ((struct Integer*)array->elems[0])->i);
        ASSERT_ISA(OT_Integer, array->elems[1]);
        EXPECT_IEQ(200, ((struct Integer*)array->elems[1])->i);
    END

    TEST(pArray_checkError1)
        const string_t src = "{";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Error, pArray(&parseState));
    END

    TEST(pPair_checkEmpty)
        const string_t src = "[]";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pPair(&parseState));
        ASSERT_ISA(OT_Pair, parseState.result);
    END

    TEST(pPair_check1Element)
        const string_t src = "[100]";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pPair(&parseState));
        ASSERT_ISA(OT_Pair, parseState.result);
        struct Pair* pair = (struct Pair*)parseState.result;
        ASSERT_ISA(OT_Integer, pair->first);
        EXPECT_IEQ(100, ((struct Integer*)pair->first)->i);
    END

    TEST(pPair_check3Elements)
        const string_t src = "[100, 200, 300]";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pPair(&parseState));
        ASSERT_ISA(OT_Pair, parseState.result);
        struct Pair* pair1 = (struct Pair*)parseState.result;
        ASSERT_ISA(OT_Integer, pair1->first);
        EXPECT_IEQ(100, ((struct Integer*)pair1->first)->i);
        ASSERT_ISA(OT_Pair, pair1->rest);
        struct Pair* pair2 = (struct Pair*)pair1->rest;
        ASSERT_ISA(OT_Integer, pair2->first);
        EXPECT_IEQ(200, ((struct Integer*)pair2->first)->i);
        ASSERT_ISA(OT_Pair, pair2->rest);
        struct Pair* pair3 = (struct Pair*)pair2->rest;
        ASSERT_ISA(OT_Integer, pair3->first);
        EXPECT_IEQ(300, ((struct Integer*)pair3->first)->i);
    END

    TEST(pPair_checkPipe)
        const string_t src = "[100 | 200]";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pPair(&parseState));
        ASSERT_ISA(OT_Pair, parseState.result);
        struct Pair* pair = (struct Pair*)parseState.result;
        ASSERT_ISA(OT_Integer, pair->first);
        EXPECT_IEQ(100, ((struct Integer*)pair->first)->i);
        ASSERT_ISA(OT_Integer, pair->rest);
        EXPECT_IEQ(200, ((struct Integer*)pair->rest)->i);
    END

    TEST(pTerm_checkEmpty)
        const string_t src = "Foo{}";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pTerm(&parseState));
        ASSERT_ISA(OT_Term, parseState.result);
        struct Term* term = (struct Term*)parseState.result;
        ASSERT_IEQ(0, term->nArgs);
    END

    TEST(pTerm_check3Args)
        const string_t src = "Foo{100, 200, 300}";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pTerm(&parseState));
        ASSERT_ISA(OT_Term, parseState.result);
        struct Term* term = (struct Term*)parseState.result;
        ASSERT_IEQ(3, term->nArgs);
        ASSERT_ISA(OT_Integer, term->args[0]);
        EXPECT_IEQ(100, ((struct Integer*)term->args[0])->i);
        ASSERT_ISA(OT_Integer, term->args[1]);
        EXPECT_IEQ(200, ((struct Integer*)term->args[1])->i);
        ASSERT_ISA(OT_Integer, term->args[2]);
        EXPECT_IEQ(300, ((struct Integer*)term->args[2])->i);
    END

    END_TESTS
}

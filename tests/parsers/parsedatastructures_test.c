#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parsedatastructures.h"
#include "object/types/integer.h"

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

    END_TESTS
}

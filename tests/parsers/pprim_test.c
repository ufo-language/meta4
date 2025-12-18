#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parserprims.h"
#include "object/globals.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

static bool_t isA(const string_t tokenType, struct Vector* tokens, index_t index) {
    if (vector_count(tokens) < index) {
        return false;
    }
    struct Term* token = (struct Term*)vector_get_unsafe(tokens, index);
    struct Symbol* expectedNameSym = symbol_new(tokenType);
    return token->name == expectedNameSym;
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Symbol* integerSym = symbol_new("Int");

    TEST(pSpot_checkEmptyTokenVector)
        const string_t src = "";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        /* The vector is not really empty; it contains EOF{EOF} */
        ASSERT_IEQ(1, vector_count(tokens));
        ASSERT_TRUE(isA("EOI", tokens, 0));
        struct Vector* results = vector_new();
        index_t index = 0;
        EXPECT_FALSE(pSpot(integerSym, tokens, &index, results));
    END

    TEST(pSpot_checkInt)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        ASSERT_IEQ(2, vector_count(tokens));
        struct Vector* results = vector_new();
        index_t index = 0;
        ASSERT_TRUE(pSpot(integerSym, tokens, &index, results));
        ASSERT_IEQ(1, vector_count(results));
        EXPECT_TRUE(isA("Int", tokens, 0));
        ASSERT_TRUE(isA("EOI", tokens, 1));
        EXPECT_IEQ(1, index);
    END

    TEST(pStrip_checkInt)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        ASSERT_IEQ(2, vector_count(tokens));
        struct Vector* results = vector_new();
        index_t index = 0;
        ASSERT_TRUE(pSpot(integerSym, tokens, &index, results));
        ASSERT_IEQ(1, vector_count(results));
        ASSERT_TRUE(isA("Int", tokens, 0));
        vector_push(results, vector_get_unsafe(tokens, 0));
        ASSERT_TRUE(pStrip(tokens, &index, results));
        struct Object* resultObj = vector_pop_unsafe(results);
        ASSERT_ISA(OT_Integer, resultObj);
    END

    END_TESTS
}

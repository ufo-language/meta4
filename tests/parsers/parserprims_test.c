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
        EXPECT_FALSE(pSpot(integerSym, tokens, &index, &result));
    END

    TEST(pSpot_checkInt)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        EXPECT_TRUE(isA("Int", vector_get_unsafe(tokens, 0)));
        ASSERT_TRUE(isA("EOI", vector_get_unsafe(tokens, 1)));
        ASSERT_IEQ(2, vector_count(tokens));
        struct Object* result = (struct Object*)g_nil;
        index_t index = 0;
        ASSERT_TRUE(pSpot(integerSym, tokens, &index, &result));
        EXPECT_IEQ(1, index);
        ASSERT_ISA(OT_Term, result);
        EXPECT_TRUE(isA("Int", result));
    END

    TEST(pStrip_checkInt)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        struct Object* result = (struct Object*)g_nil;
        index_t index = 0;
        ASSERT_TRUE(pSpot(integerSym, tokens, &index, &result));
        ASSERT_IEQ(1, index);
        ASSERT_TRUE(pStrip(tokens, &index, &result));
        ASSERT_ISA(OT_Integer, result);
    END

    END_TESTS
}

#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "lexer/lexer.h"
#include "lexer/syntax.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/real.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

bool_t tokenTypeIs(const char* typeName, struct Term* token) {
    return strcmp(token->name->name, typeName) ? false : true;
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    /* Check separate token types */

    TEST(lexer_checkEmptyString)
        const string_t src = "";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(1, vector_count(tokens));
        /* First token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[0]));
    END

    TEST(lexer_checkInteger_positive)
        const string_t src = "123";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(123, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkInteger_negative)
        const string_t src = "-123";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(-123, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkInteger_withPlus)
        const string_t src = "+123";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(123, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkHexInt)
        const string_t src = "0x1FF";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(511, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkNegativeHexInt)
        const string_t src = "-0x1FF";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(-511, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkBinInt)
        const string_t src = "0b1000";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(8, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkNegativeBinInt)
        const string_t src = "-0b1000";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Int", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Integer, arg);
        ASSERT_IEQ(-8, ((struct Integer*)arg)->i);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkReal)
        /* Make sure that this is a number that can be represented exactly in binary */
        const string_t src = "1234.5";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Real", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Real, arg);
        EXPECT_REQ(1234.5, ((struct Real*)arg)->r);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkString)
        /* Make sure that this is a number that can be represented exactly in binary */
        const string_t src = "\"abc\"";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("String", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_String, arg);
        EXPECT_IEQ(0, strcmp("abc", ((struct String*)arg)->chars));
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkIdentifier)
        const string_t src = "abc";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Ident", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Identifier, arg);
        EXPECT_IEQ(0, strcmp("abc", ((struct Identifier*)arg)->name));
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkReservedWord)
        const string_t src = "end";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Reserved", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_String, arg);
        EXPECT_IEQ(0, strcmp("end", ((struct String*)arg)->chars));
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkOperator)
        const string_t src = "++";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Oper", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Identifier, arg);
        EXPECT_IEQ(0, strcmp("++", ((struct Identifier*)arg)->name));
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkSymbol)
        const string_t src = "Abc";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Symbol", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Symbol, arg);
        EXPECT_IEQ(0, strcmp("Abc", ((struct Symbol*)arg)->name));
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkSpecialChar)
        const string_t src = "{";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Special", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_String, arg);
        EXPECT_IEQ(0, strcmp("{", ((struct String*)arg)->chars));
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    /* Check multiple tokens */

    TEST(lexer_checkLexAll)
        const string_t src = "abc 123 +-* \"def\" Gji";
        struct Vector* tokens = vector_new();
        lexer_lexAll(syntax, src, tokens);
        ASSERT_IEQ(6, vector_count(tokens));
        SHOW("tokens", tokens);
        /* TODO check the type of each token */
    END

    END_TESTS
}

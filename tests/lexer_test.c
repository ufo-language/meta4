#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "lexer/lexer.h"
#include "lexer/syntax.h"
#include "object/types/identifier.h"
#include "object/types/intarray.h"
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
        ASSERT_IEQ(1, vector_count(tokens));
        /* First token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[0]));
    END

    TEST(lexer_checkInteger_positive)
        const string_t src = "123";
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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

    TEST(lexer_checkPositiveReal)
        /* Make sure that this is a number that can be represented exactly in binary */
        const string_t src = "+1234.5";
        struct Vector* tokens = lexer_lexAll(syntax, src);
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

    TEST(lexer_checkNegativeReal)
        /* Make sure that this is a number that can be represented exactly in binary */
        const string_t src = "-1234.5";
        struct Vector* tokens = lexer_lexAll(syntax, src);
        ASSERT_IEQ(2, vector_count(tokens));
        /* First token */
        struct Term* token = (struct Term*)tokens->elems->elems[0];
        ASSERT_TRUE(tokenTypeIs("Real", token));
        ASSERT_IEQ(1, token->nArgs);
        struct Object* arg = token->args[0];
        ASSERT_ISA(OT_Real, arg);
        EXPECT_REQ(-1234.5, ((struct Real*)arg)->r);
        /* Second token */
        ASSERT_TRUE(tokenTypeIs("EOI", (struct Term*)tokens->elems->elems[1]));
    END

    TEST(lexer_checkString)
        /* Make sure that this is a number that can be represented exactly in binary */
        const string_t src = "\"abc\"";
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        struct Vector* tokens = lexer_lexAll(syntax, src);
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
        const count_t nTokens = 8;
        const string_t src = "abc (123)\n+-* \"def\" Ghi";
        /*                    000000000 01111 1111 112222 */
        /*                    012345678 90123 4567 890123 */
        struct Vector* tokens = lexer_lexAll(syntax, src);
        ASSERT_IEQ(nTokens, vector_count(tokens));
        SHOW("tokens", tokens);
        /*
        Ident{abc}   %IntArray{0, 1, 1}
        Special{"("} %IntArray{4, 1, 5}
        Int{123}     %IntArray{5, 1, 6}
        Special{")"} %IntArray{8, 1, 9}
        Oper{+-*}    %IntArray{10, 2, 1}
        String{"def"}%IntArray{14, 2, 5}
        Symbol{Ghi}  %IntArray{20, 2, 11}
        EOI{EOI}     %IntArray{23, 2, 14}|}
        */
        /* Check the position of each token */
        index_t indexes[] = {0, 4, 5, 8, 10, 14, 20, 23};
        index_t lines[] = {1, 1, 1, 1, 2, 2, 2, 2};
        index_t cols[] = {1, 5, 6, 9, 1, 5, 11, 14};
        for (index_t n=0; n<nTokens; ++n) {
            struct Object* tokenObj;
            vector_get(tokens, n, &tokenObj);
            struct Object* attribObj = ((struct Term*)tokenObj)->attrib;
            struct IntArray* attrib = (struct IntArray*)attribObj;
            index_t expectedIndex = indexes[n];
            index_t expectedLine = lines[n];
            index_t expectedCol = cols[n];
            index_t index = attrib->elems[0];
            index_t tokenLine = attrib->elems[1];
            index_t tokenCol = attrib->elems[2];
            SHOW("Token", tokenObj);
            EXPECT_IEQ(expectedIndex, index);
            EXPECT_IEQ(expectedLine, tokenLine);
            EXPECT_IEQ(expectedCol, tokenCol);
        }
    END

    END_TESTS
}

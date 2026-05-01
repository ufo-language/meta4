#include "_test.h"
#include "_typedefs.h"

#include "lexer/syntax.h"
#include "parsers/parsedatastructures.h"
#include "object/types/binding.h"
#include "object/types/integer.h"
#include "object/types/symbol.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Vector* tokens = vector_new();

    TEST(pBinding_checkSimple)
        const string_t src = "X = 100";
        vector_clear(tokens);
        tokens = lexer_lexAll_withVector(syntax, src, tokens);
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        ASSERT_IEQ(PRS_Pass, pBinding(&parseState));
        ASSERT_ISA(OT_Binding, parseState.result);
        struct Binding* binding = (struct Binding*)parseState.result;
        ASSERT_ISA(OT_Symbol, binding->key);
        struct Symbol* keySym = (struct Symbol*)binding->key;
        EXPECT_TRUE(string_compare_chars(keySym->name, "X") == CompareResult_Equal);
        ASSERT_ISA(OT_Integer, binding->value);
        struct Integer* intVal = (struct Integer*)binding->value;
        EXPECT_IEQ(100, intVal->i);
    END

    END_TESTS
}

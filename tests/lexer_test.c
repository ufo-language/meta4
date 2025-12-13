#include "_test.h"
#include "_typedefs.h"

#include "lexer/lexer.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(lexer_checkLexAll)
        char* s = "abc Abc -123 0x34 0b101 3.14159";
        struct Vector* tokens = vector_new();
        lexer_lexAll(s, tokens);
        SHOW("tokens", tokens);
    END

    END_TESTS
}

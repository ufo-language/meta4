#include "_test.h"
#include "_typedefs.h"

#include "lexer/lexer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

#if 1
    TEST(lexer_checkLexAll)
        char* s = "abc Abc -123 0x34 0b101 3.14159";
        lexer_lexAll(s);
    END
#else
    TEST(lexer2_checkLexAll)
        char* s = "abc Abc 123";
        lexer2_lexAll(s);
    END
#endif

    END_TESTS
}

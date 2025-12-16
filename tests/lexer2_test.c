#include "_test.h"
#include "_typedefs.h"

#include "lexer2/lexer2.h"
#include "lexer2/syntax.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

   TEST(lexer_checkLexAll)
        // const string_t src = "abc Abc 123 \"Hello\"";
        const string_t src = "abc 123";
        struct Vector* tokens = vector_new();
        //void lexer2_lexAll(struct Transition** syntax, const string_t sourceString,
//                               struct Vector* tokens) {

        lexer2_lexAll(syntax, src, tokens);
        SHOW("tokens", tokens);
    END


    END_TESTS
}

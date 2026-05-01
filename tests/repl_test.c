#include <stdio.h>
#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "lexer/lexer.h"
#include "lexer/syntax.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/types/outstream.h"
#include "parsers/parseany.h"
#include "parsers/parser.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(repl_check100)
        const string_t input = "100";
        struct Vector* tokens = lexer_lexAll(syntax, input);
        
        struct ParseState parseState;
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAny, &parseState);
        
        ASSERT_EQ(PRS_Pass, parseResult);
        
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value = NULL;
        bool_t evalSuccess = etor_rec_run(etor, parseState.result, &value);
        
        ASSERT_TRUE(evalSuccess);
        
        EXPECT_SHOW("100", value);
        EXPECT_ISA(OT_Integer, value);
    END

    END_TESTS
}

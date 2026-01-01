#include "_test.h"
#include "_typedefs.h"

#include "parsers/parsememotable.h"
#include "object/types/integer.h"
#include "object/types/vector.h"

/*
bool_t parser_memoLookup(struct Vector* memoVector,
                         ParserFunction parserFunction,
                         index_t tokenIndex,
                         enum ParseResultStatus* parseResult,
                         struct Object** resultObj);


void parser_memoizeResult(struct Vector* memoVector,
                          ParserFunction parserFunction,
                          index_t tokenIndex,
                          enum ParseResultStatus status,
                          struct Object* resultObj);
*/


/* typedef enum ParseResultStatus (*ParserFunction)(struct ParseState* parseState);
*/

struct Integer* i100;
struct Integer* i200;

enum ParseResultStatus pf1(struct ParseState* parseState);
enum ParseResultStatus pf2(struct ParseState* parseState);

enum ParseResultStatus pf1(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Pass;
}

enum ParseResultStatus pf2(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Pass;
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    i100 = integer_new(100);
    i200 = integer_new(200);

    TEST(parseMemoTable_check1)
        struct Vector* memoVector = vector_new();
        enum ParseResultStatus status;
        struct Object* resultObj;
        EXPECT_FALSE(parser_memoLookup(memoVector, pf1, 0, &status, &resultObj));
        parser_memoizeResult(memoVector, pf1, 0, PRS_Pass, (struct Object*)i100);
        EXPECT_TRUE(parser_memoLookup(memoVector, pf1, 0, &status, &resultObj));
        EXPECT_IEQ(PRS_Pass, status);
        EXPECT_EQ(i100, resultObj);
        EXPECT_FALSE(parser_memoLookup(memoVector, pf2, 0, &status, &resultObj));
        EXPECT_FALSE(parser_memoLookup(memoVector, pf1, 1, &status, &resultObj));
        parser_memoizeResult(memoVector, pf1, 1, PRS_Pass, (struct Object*)i200);
        /* Retry first lookup to be sure the value is the same */
        EXPECT_TRUE(parser_memoLookup(memoVector, pf1, 0, &status, &resultObj));
        EXPECT_IEQ(PRS_Pass, status);
        EXPECT_EQ(i100, resultObj);
        /* No try the second lookup */
        EXPECT_TRUE(parser_memoLookup(memoVector, pf1, 1, &status, &resultObj));
        EXPECT_IEQ(PRS_Pass, status);
        EXPECT_EQ(i200, resultObj);
    END

    END_TESTS
}

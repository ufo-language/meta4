#include "_typedefs.h"

#include "object/types/array.h"
#include "object/types/vector.h"
#include "parsers/parser.h"
#include "parsers/parseany.h"
#include "parsers/parsedatastructures.h"
#include "parsers/parserprims.h"
#include "parsers/parsespecialchars.h"
#include "parsers/parseoperators.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pArray(struct ParseState* parseState) {
    enum ParseResultStatus parseResult = pListOf(pSpecialOpenBrace, pAny, pSpecialComma, pSpecialCloseBrace, parseState);
    if (parseResult == PRS_Pass) {
        struct Vector* elems = (struct Vector*)parseState->result;
        struct Array* array = array_fromVector(elems);
        parseState->result = (struct Object*)array;
    }
    return parseResult;
}

enum ParseResultStatus pBinding(struct ParseState* parseState) {
    ParserFunction parsers[] = {pAny, pOperatorEqual, pAny};
    enum ParseResultStatus status = pSequence(3, parsers, parseState);

    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pHashTable(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pPair(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pQueue(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pSet(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pTerm(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pVector(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

/* Private functions *********************************************************/

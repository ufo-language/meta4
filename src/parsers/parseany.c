#include "_typedefs.h"

#include "parsers/parseany.h"
#include "parsers/parsedatastructures.h"
#include "parsers/parseliterals.h"
#include "parsers/parser.h"
#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pAny(struct ParseState* parseState) {
    static count_t nParsers = 4;
    static ParserFunction parsers[] = {pArray, pPair, pTerm, pLiteral};
    return pOneOf(nParsers, parsers, parseState);
}

enum ParseResultStatus pAnyOrBinding(struct ParseState* parseState) {
    static count_t nParsers = 2;
    static ParserFunction parsers[] = {pBinding, pAny};
    return pOneOf(nParsers, parsers, parseState);
}

/* Private functions *********************************************************/

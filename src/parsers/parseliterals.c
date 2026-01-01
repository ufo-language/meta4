#include "_typedefs.h"

#include "object/globals.h"
#include "parsers/parseliterals.h"
#include "parsers/parser.h"
#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pLiteral(struct ParseState* parseState) {
    static count_t nParsers = 7;
    static ParserFunction parsers[] = {pBoolean, pIdentifier, pInteger, pNil, pReal, pString, pSymbol};
    enum ParseResultStatus parseResult = pOneOf(nParsers, parsers, parseState);
    if (parseResult == PRS_Pass) {
        pStrip(parseState);
    }
        return parseResult;
}

enum ParseResultStatus pBoolean(struct ParseState* parseState) {
    return pSpot(g_symBoolean, parseState);
}

enum ParseResultStatus pIdentifier(struct ParseState* parseState) {
    return pSpot(g_symIdentifier, parseState);
}

enum ParseResultStatus pInteger(struct ParseState* parseState) {
    return pSpot(g_symInteger, parseState);
}

enum ParseResultStatus pNil(struct ParseState* parseState) {
    return pSpot(g_symNil, parseState);
}

enum ParseResultStatus pReal(struct ParseState* parseState) {
    return pSpot(g_symReal, parseState);
}

enum ParseResultStatus pString(struct ParseState* parseState) {
    return pSpot(g_symString, parseState);
}

enum ParseResultStatus pSymbol(struct ParseState* parseState) {
    return pSpot(g_symSymbol, parseState);
}

/* Private functions *********************************************************/

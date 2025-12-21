#include "_typedefs.h"

#include "object/globals.h"
#include "parsers/parser.h"
#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pBoolean(struct ParseState* parseState) {
    return pSpot(g_symBoolean, parseState);
}

enum ParseStatus pIdentifier(struct ParseState* parseState) {
    return pSpot(g_symIdentifier, parseState);
}

enum ParseStatus pInteger(struct ParseState* parseState) {
    return pSpot(g_symInteger, parseState);
}

enum ParseStatus pNil(struct ParseState* parseState) {
    return pSpot(g_symNil, parseState);
}

enum ParseStatus pReal(struct ParseState* parseState) {
    return pSpot(g_symReal, parseState);
}

enum ParseStatus pString(struct ParseState* parseState) {
    return pSpot(g_symString, parseState);
}

enum ParseStatus pSymbol(struct ParseState* parseState) {
    return pSpot(g_symSymbol, parseState);
}

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/string.h"
#include "object/types/term.h"
#include "parsers/parser.h"
#include "parsers/parserprims.h"
#include "parsers/parsespecialchars.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

enum ParseResultStatus pSpotSpecialChar(char c, struct ParseState* parseState);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pSpotSpecialChar(char c, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseResultStatus status = pSpot(g_symSpecial, parseState);
    if (status == PRS_Pass) {
        struct Term* token = (struct Term*)parseState->result;
        if (token->nArgs == 1) {
            struct Object* arg = token->args[0];
            if (arg->typeId == OT_String) {
                struct String* argString = (struct String*)arg;
                if (argString->nChars == 1 && argString->chars[0] == c) {
                    return PRS_Pass;
                }
            }
        }
    }
    parseState->index = savedIndex;
    return PRS_Fail;
}

enum ParseResultStatus pSpecialOpenBrace(struct ParseState* parseState) {
    return pSpotSpecialChar('{', parseState);
}

enum ParseResultStatus pSpecialCloseBrace(struct ParseState* parseState) {
    return pSpotSpecialChar('}', parseState);
}

enum ParseResultStatus pSpecialOpenBracket(struct ParseState* parseState) {
    return pSpotSpecialChar('[', parseState);
}

enum ParseResultStatus pSpecialCloseBracket(struct ParseState* parseState) {
    return pSpotSpecialChar(']', parseState);
}

enum ParseResultStatus pSpecialOpenParen(struct ParseState* parseState) {
    return pSpotSpecialChar('(', parseState);
}

enum ParseResultStatus pSpecialCloseParen(struct ParseState* parseState) {
    return pSpotSpecialChar(')', parseState);
}

enum ParseResultStatus pSpecialComma(struct ParseState* parseState) {
    return pSpotSpecialChar(',', parseState);
}

enum ParseResultStatus pSpecialSemicolon(struct ParseState* parseState) {
    return pSpotSpecialChar(';', parseState);
}

enum ParseResultStatus pSpecialEqual(struct ParseState* parseState) {
    return pSpotSpecialChar('=', parseState);
}

enum ParseResultStatus pSpecialPipe(struct ParseState* parseState) {
    return pSpotSpecialChar('|', parseState);
}

/* Private functions --------------------------------------------------------*/


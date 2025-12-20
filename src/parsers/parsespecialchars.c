#include "_typedefs.h"

#include "object/globals.h"
#include "parsers/parsestate.h"
#include "parsers/parserprims.h"
#include "object/types/string.h"
#include "object/types/term.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pSpotSpecialChar(char c, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseStatus status = pSpot(g_symSpecial, parseState);
    if (status == PS_Success) {
        struct Term* token = (struct Term*)parseState->result;
        if (token->nArgs == 1) {
            struct Object* arg = token->args[0];
            if (arg->typeId == OT_String) {
                struct String* argString = (struct String*)arg;
                if (argString->nChars == 1 && argString->chars[0] == c) {
                    return PS_Success;
                }
            }
        }
    }
    parseState->index = savedIndex;
    return PS_Fail;
}

enum ParseStatus pSpecialOpenBrace(struct ParseState* parseState) {
    return pSpotSpecialChar('{', parseState);
}

/* Private functions *********************************************************/


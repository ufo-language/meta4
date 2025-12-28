#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/string.h"
#include "object/types/term.h"
#include "parsers/parser.h"
#include "parsers/parsereservedwords.h"
#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pSpotReserved(const string_t word, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseStatus status = pSpot(g_symReserved, parseState);
    if (status == PS_Success) {
        struct Term* token = (struct Term*)parseState->result;
        if (token->nArgs == 1) {
            struct Object* arg = token->args[0];
            if (arg->typeId == OT_String) {
                struct String* argString = (struct String*)arg;
                if (string_compare_chars(argString->chars, word) == CompareEqual) {
                    return PS_Success;
                }
            }
        }
    }
    parseState->index = savedIndex;
    return PS_Fail;
}

enum ParseStatus pReservedEnd(struct ParseState* parseState) {
    return pSpotReserved("end", parseState);
}

/* Private functions *********************************************************/

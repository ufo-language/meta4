#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/string.h"
#include "object/types/term.h"
#include "parsers/parser.h"
#include "parsers/parserprims.h"
#include "parsers/parseoperators.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

enum ParseResultStatus pSpotOperator(const string_t string, struct ParseState* parseState);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pSpotOperator(const string_t string, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseResultStatus status = pSpot(g_symOperator, parseState);
    if (status == PRS_Pass) {
        struct Term* token = (struct Term*)parseState->result;
        if (token->nArgs == 1) {
            struct Object* arg = token->args[0];
            if (arg->typeId == OT_String) {
                struct String* argString = (struct String*)arg;
                if (string_compare_chars(argString->chars, string) == CompareResult_Equal) {
                    return PRS_Pass;
                }
            }
        }
    }
    parseState->index = savedIndex;
    return PRS_Fail;
}

enum ParseResultStatus pOperatorEqual(struct ParseState* parseState) {
    return pSpotOperator("=", parseState);
}

/* Private functions *********************************************************/


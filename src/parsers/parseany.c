#include "_typedefs.h"

#include "parsers/parseany.h"
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
    static count_t nParsers = 1;
    static ParserFunction parsers[] = {pLiteral};
    return pOneOf(nParsers, parsers, parseState);
}

/* Private functions *********************************************************/

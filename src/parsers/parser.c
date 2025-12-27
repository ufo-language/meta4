#include "_typedefs.h"

#include "object/types/intvector.h"
#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus parse(ParserFunction parser, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseStatus status = parser(parseState);
    intVector_set_raw(parseState->memoVector, savedIndex, (int_t)status);
    return status;
}

/* Private functions *********************************************************/

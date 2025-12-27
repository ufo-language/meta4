#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
#include "object/types/intvector.h"
#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ParseState* parseState_new(struct Vector* tokens) {
    struct ParseState* parseState = (struct ParseState*)memory_alloc(NWORDS(struct ParseState));
    parseState_init(parseState, tokens);
    return parseState;
}

void parseState_init(struct ParseState* parseState, struct Vector* tokens) {
    parseState->tokens = tokens;
    parseState->index = 0;
    parseState->result = g_uniqueObject;
    parseState->memoVector = intVector_new();
}

/* Public functions **********************************************************/

enum ParseStatus parse(ParserFunction parser, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseStatus status = parser(parseState);
    intVector_set_raw(parseState->memoVector, savedIndex, (int_t)status);
    return status;
}

/* Private functions *********************************************************/

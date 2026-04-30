#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
#include "object/types/vector.h"
#include "parsers/parser.h"
#include "parsers/parsememotable.h"

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
    parseState->memoVector = vector_new();
}

/* Public functions **********************************************************/

enum ParseResultStatus parse(ParserFunction parser, struct ParseState* parseState) {
    enum ParseResultStatus status;
    struct Object* resultObj;
    if (parser_memoLookup(parseState->memoVector, parser, parseState->index, &status, &resultObj)) {
        parseState->result = resultObj;
        return status;
    }
    /* TODO does adding the recursion barrier here cause any problems?
        -> Yes, it's too strong. */
    // parser_addRecursionBarrier(parser, parseState);
    index_t savedIndex = parseState->index;
    status = parser(parseState);
    if (status != PRS_Pass) {
        parseState->index = savedIndex;
    }
    parser_memoizeResult(parseState->memoVector, parser, savedIndex, status, parseState->result);
    return status;
}

/* Private functions *********************************************************/

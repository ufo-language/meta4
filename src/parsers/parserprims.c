#include "_typedefs.h"

#include "parsers/parserprims.h"
#include "parsers/parsestate.h"
#include "object/globals.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

#include "debug.h"

enum ParseStatus pIgnore(ParserFunction parser, struct ParseState* parseState) {
    enum ParseStatus parseStatus = parser(parseState);
    if (parseStatus == PS_Success) {
        parseState->result = g_uniqueObject;
    }
    return parseStatus;
}

enum ParseStatus pOneOf(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    for (index_t n=0; n<nParsers; ++n) {
        enum ParseStatus parseStatus = parsers[n](parseState);
        switch (parseStatus) {
            case PS_Fail:
                break;
            case PS_Success:
            case PS_Error:
                return parseStatus;
        }
        parseState->index = savedIndex;
    }
    return PS_Fail;
}

enum ParseStatus pSepBy(ParserFunction elem, ParserFunction separator, count_t minElems, struct ParseState* parseState) {
    struct Vector* elems = vector_new();
    count_t nElems = 0;
    index_t savedIndex = parseState->index;
    bool_t contin = true;
    while (contin) {
        switch (elem(parseState)) {
            case PS_Success:
                vector_push(elems, parseState->result);
                ++nElems;
                switch (separator(parseState)) {
                    case PS_Success:
                        break;
                    case PS_Fail:
                        contin = false;
                        break;
                    case PS_Error:
                        return PS_Error;
                }
                break;
            case PS_Fail:
                if (nElems > 0) {
                    // ERROR: element expected after separator
                    return PS_Error;
                }
                contin = false;
                break;
            case PS_Error:
                return PS_Error;
        }
    }
    if (nElems < minElems) {
        parseState->index = savedIndex;
        return PS_Fail;
    }
    parseState->result = (struct Object*)elems;
    return PS_Success;
}

enum ParseStatus pSequence(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    struct Vector* results = vector_new();
    for (index_t n=0; n<nParsers; ++n) {
        enum ParseStatus parseStatus = parsers[n](parseState);
        switch (parseStatus) {
            case PS_Success:
                if (parseState->result != g_uniqueObject) {
                    vector_push(results, parseState->result);
                }
                break;
            case PS_Fail:
                parseState->index = savedIndex;
                return PS_Fail;
            case PS_Error:
                return PS_Error;
        }
    }
    switch (vector_count(results)) {
        case 0:
            parseState->result = (struct Object*)g_nil;
            break;
        case 1:
            parseState->result = vector_pop_unsafe(results);
            break;
        default:
            parseState->result = (struct Object*)results;
            break;
    }
    return PS_Success;
}

enum ParseStatus pSpot(struct Symbol* tokenType, struct ParseState* parseState) {
    struct Object* tokenObj = parseState->tokens->elems->elems[parseState->index];
    if (((struct Term*)tokenObj)->name == tokenType) {
        ++(parseState->index);
        parseState->result = tokenObj;
        return PS_Success;
    }
    return PS_Fail;
}

enum ParseStatus pStrip(struct ParseState* parseState) {
    parseState->result = ((struct Term*)parseState->result)->args[0];
    return PS_Success;
}

/* Private functions *********************************************************/

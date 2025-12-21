#include "_typedefs.h"

#include "parsers/parserprims.h"
#include "parsers/parsestate.h"
#include "object/globals.h"
#include "object/functions/show.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/


static void _indent(count_t level) {
    for (count_t n=0; n<level; n++) {
        fputs("│ ", stderr);
    }
}

static count_t debugLevel = 0;

enum ParseStatus pDebug(ParserFunction parser, const string_t message, struct ParseState* parseState) {
    static string_t statusNames[] = {"Pass", "Fail", "Error"};
    _indent(debugLevel);
    fprintf(stderr, "┌ DEBUG: %s, token = ", message);
    struct Object* token = (struct Object*)parseState->tokens->elems->elems[parseState->index];
    show(token, g_stderr);
    fputc('\n', stderr);
    ++debugLevel;
    enum ParseStatus status = parser(parseState);
    --debugLevel;
    _indent(debugLevel);
    fprintf(stderr, "└ STATUS: %s, result = ", statusNames[status]);
    show(parseState->result, g_stderr);
    fputc('\n', stderr);
    return status;
}

enum ParseStatus pEnsure(ParserFunction parser, const string_t message, struct ParseState* parseState) {
    enum ParseStatus status = parser(parseState);
    if (status == PS_Fail) {
        struct String* messageString = string_new(message);
        parseState->result = (struct Object*)messageString;
        return PS_Error;
    }
    return status;
}

enum ParseStatus pError(const string_t message, struct ParseState* parseState) {
    struct String* messageString = string_new(message);
    parseState->result = (struct Object*)messageString;
    return PS_Error;
}

enum ParseStatus pIgnore(ParserFunction parser, struct ParseState* parseState) {
    enum ParseStatus parseStatus = parser(parseState);
    if (parseStatus == PS_Success) {
        parseState->result = g_uniqueObject;
    }
    return parseStatus;
}

enum ParseStatus pListOf(ParserFunction open, ParserFunction elem, ParserFunction sep, ParserFunction close, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseStatus status = open(parseState);
    if (status != PS_Success) {
        parseState->index = savedIndex;
        return status;
    }
    status = pSepBy(elem, sep, 0, parseState);
    if (status != PS_Success) {
        parseState->index = savedIndex;
        return status;
    }
    struct Vector* elems = (struct Vector*)parseState->result;
    status = close(parseState);
    if (status != PS_Success) {
        parseState->index = savedIndex;
        return status;
    }
    parseState->result = (struct Object*)elems;
    return PS_Success;
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
    if (tokenObj->typeId != OT_Term) {
        return PS_Fail;
    }
    struct Term* token = (struct Term*)tokenObj;
    if (token->name == tokenType) {
        ++(parseState->index);
        parseState->result = tokenObj;
        return PS_Success;
    }
    return PS_Fail;
}

#if 0
enum ParseStatus pSpotSpecific(struct Symbol* tokenType, const string_t tokenString, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseStatus status = pSpot(tokenType, parseState);
    if (status == PS_Success) {
        struct Term* token = (struct Term*)parseState->result;
        if (token->nArgs == 1) {
            struct Object* argObj = token->args[0];
            if (argObj->typeId == OT_String) {
                struct String* argString = (struct String*)argObj;
                if (string_equal_chars(argString, tokenString)) {
                    return PS_Success;
                }
            }
        }
    }
    parseState->index = savedIndex;
    return PS_Fail;
}
#endif

enum ParseStatus pStrip(struct ParseState* parseState) {
    parseState->result = ((struct Term*)parseState->result)->args[0];
    return PS_Success;
}

/* Private functions *********************************************************/

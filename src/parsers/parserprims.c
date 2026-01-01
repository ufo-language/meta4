#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"
#include "parsers/parser.h"
#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

struct Object* _currentLocation(struct ParseState* parseState);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/


static void _indent(count_t level) {
    for (count_t n=0; n<level; n++) {
        fputs("│ ", stderr);
    }
}

static count_t debugLevel = 0;

enum ParseResultStatus pDebug(ParserFunction parser, const string_t message, struct ParseState* parseState) {
    static string_t statusNames[] = {"Pass", "Fail", "Error"};
    _indent(debugLevel);
    fprintf(stderr, "┌ DEBUG: %s, token = ", message);
    struct Object* token = (struct Object*)parseState->tokens->elems->elems[parseState->index];
    show(token, g_stderr);
    fputc('\n', stderr);
    ++debugLevel;
    enum ParseResultStatus status = parse(parser, parseState);
    --debugLevel;
    _indent(debugLevel);
    fprintf(stderr, "└ STATUS: %s, result = ", statusNames[status]);
    show(parseState->result, g_stderr);
    fputc('\n', stderr);
    return status;
}

enum ParseResultStatus pEnsure(ParserFunction parser, const string_t message, struct ParseState* parseState) {
    enum ParseResultStatus status = parse(parser, parseState);
    if (status == PRS_Fail) {
        parseState->result = (struct Object*)errorTerm1("ParseError", message, _currentLocation(parseState));
        return PRS_Error;
    }
    return status;
}

enum ParseResultStatus pError(const string_t message, struct ParseState* parseState) {
    parseState->result = (struct Object*)errorTerm1("ParseError", message, _currentLocation(parseState));
    return PRS_Error;
}

enum ParseResultStatus pIgnore(ParserFunction parser, struct ParseState* parseState) {
    enum ParseResultStatus parseResult = parse(parser, parseState);
    if (parseResult == PRS_Pass) {
        parseState->result = g_uniqueObject;
    }
    return parseResult;
}

enum ParseResultStatus pListOf(ParserFunction open, ParserFunction elem, ParserFunction sep, ParserFunction close, struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    enum ParseResultStatus status = parse(open, parseState);
    if (status != PRS_Pass) {
        parseState->index = savedIndex;
        return status;
    }
    status = pSepBy(elem, sep, 0, parseState);
    if (status != PRS_Pass) {
        // TODO create error term before restoring index
        parseState->result = (struct Object*)errorTerm1("ParseError",
            "Element separator expected", _currentLocation(parseState));
        parseState->index = savedIndex;
        return PRS_Error;
    }
    struct Vector* elems = (struct Vector*)parseState->result;
    status = parse(close, parseState);
    if (status != PRS_Pass) {
        parseState->result = (struct Object*)errorTerm1("ParseError",
            "Closing token expected", _currentLocation(parseState));        parseState->index = savedIndex;
        return PRS_Error;
    }
    parseState->result = (struct Object*)elems;
    return PRS_Pass;
}

enum ParseResultStatus pOneOf(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    for (index_t n=0; n<nParsers; ++n) {
        enum ParseResultStatus parseResult = parse(parsers[n], parseState);
        switch (parseResult) {
            case PRS_Fail:
                break;
            case PRS_Pass:
            case PRS_Error:
                return parseResult;
        }
        parseState->index = savedIndex;
    }
    return PRS_Fail;
}

enum ParseResultStatus pSepBy(ParserFunction elem, ParserFunction separator, count_t minElems, struct ParseState* parseState) {
    struct Vector* elems = vector_new();
    count_t nElems = 0;
    index_t savedIndex = parseState->index;
    bool_t contin = true;
    while (contin) {
        switch (parse(elem, parseState)) {
            case PRS_Pass:
                vector_push(elems, parseState->result);
                ++nElems;
                switch (parse(separator, parseState)) {
                    case PRS_Pass:
                        break;
                    case PRS_Fail:
                        contin = false;
                        break;
                    case PRS_Error:
                        return PRS_Error;
                }
                break;
            case PRS_Fail:
                if (nElems > 0) {
                    parseState->result = (struct Object*)errorTerm1("ParseError",
                        "Element expected after separator expected", _currentLocation(parseState));
                    return PRS_Error;
                }
                contin = false;
                break;
            case PRS_Error:
                return PRS_Error;
        }
    }
    if (nElems < minElems) {
        parseState->result = (struct Object*)errorTerm1("ParseError",
            "Minimum number of elements not reached", _currentLocation(parseState));
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    parseState->result = (struct Object*)elems;
    return PRS_Pass;
}

enum ParseResultStatus pSequence(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    struct Vector* results = vector_new();
    for (index_t n=0; n<nParsers; ++n) {
        enum ParseResultStatus parseResult = parse(parsers[n], parseState);
        switch (parseResult) {
            case PRS_Pass:
                if (parseState->result != g_uniqueObject) {
                    vector_push(results, parseState->result);
                }
                break;
            case PRS_Fail:
                parseState->index = savedIndex;
                return PRS_Fail;
            case PRS_Error:
                return PRS_Error;
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
    return PRS_Pass;
}

enum ParseResultStatus pSpot(struct Symbol* tokenType, struct ParseState* parseState) {
    struct Object* tokenObj = parseState->tokens->elems->elems[parseState->index];
    if (tokenObj->typeId != OT_Term) {
        return PRS_Fail;
    }
    struct Term* token = (struct Term*)tokenObj;
    if (token->name == tokenType) {
        ++(parseState->index);
        parseState->result = tokenObj;
        return PRS_Pass;
    }
    return PRS_Fail;
}

enum ParseResultStatus pStrip(struct ParseState* parseState) {
    parseState->result = ((struct Term*)parseState->result)->args[0];
    return PRS_Pass;
}

/* Private functions *********************************************************/

struct Object* _currentLocation(struct ParseState* parseState) {
    struct Object* token = parseState->tokens->elems->elems[parseState->index];
    return token;
}

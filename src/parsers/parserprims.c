#include "_typedefs.h"

#include "parsers/parserprims.h"
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

enum ParseStatus pIgnore(ParserFunction parser, struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    enum ParseStatus parseStatus = parser(tokens, tokenIndex, result);
    if (parseStatus == PS_Success) {
        *result = g_uniqueObject;
    }
    return parseStatus;
}

enum ParseStatus pOneOf(count_t nParsers, ParserFunction parsers[], struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    index_t savedIndex = *tokenIndex;
    for (index_t n=0; n<nParsers; ++n) {
        enum ParseStatus parseStatus = parsers[n](tokens, tokenIndex, result);
        switch (parseStatus) {
            case PS_Fail:
                break;
            case PS_Success:
            case PS_Error:
                return parseStatus;
        }
        *tokenIndex = savedIndex;
    }
    return PS_Fail;
}

enum ParseStatus pSequence(count_t nParsers, ParserFunction parsers[], struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    index_t savedIndex = *tokenIndex;
    struct Object* innerResult;
    struct Vector* results = vector_new();
    for (index_t n=0; n<nParsers; ++n) {
        enum ParseStatus parseStatus = parsers[n](tokens, tokenIndex, &innerResult);
        switch (parseStatus) {
            case PS_Success:
                if (innerResult != g_uniqueObject) {
                    vector_push(results, innerResult);
                }
                break;
            case PS_Fail:
                *tokenIndex = savedIndex;
                return PS_Fail;
            case PS_Error:
                *result = innerResult;
                return PS_Error;
        }
    }
    switch (vector_count(results)) {
        case 0:
            *result = (struct Object*)g_nil;
            break;
        case 1:
            *result = vector_pop_unsafe(results);
            break;
        default:
            *result = (struct Object*)results;
            break;
    }
    return PS_Success;
}

enum ParseStatus pSpot(struct Symbol* tokenType, struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    struct Object* tokenObj = tokens->elems->elems[*tokenIndex];
    if (((struct Term*)tokenObj)->name == tokenType) {
        ++(*tokenIndex);
        *result = tokenObj;
        return PS_Success;
    }
    return PS_Fail;
}

enum ParseStatus pStrip(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    *result = ((struct Term*)*result)->args[0];
    return PS_Success;
}

/* Private functions *********************************************************/

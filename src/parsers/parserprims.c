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

bool_t pSequence(count_t nParsers, ParserFunction parsers[], struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    index_t savedIndex = *tokenIndex;
    struct Object* innerResult;
    struct Vector* results = vector_new();
    for (index_t n=0; n<nParsers; n++) {
        if (parsers[n](tokens, tokenIndex, &innerResult)) {
            if (innerResult != g_uniqueObject) {
                vector_push(results, innerResult);
            }
        }
        else {
            *tokenIndex = savedIndex;
            return false;
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
    return true;
}

bool_t pSpot(struct Symbol* tokenType, struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    struct Object* tokenObj = tokens->elems->elems[*tokenIndex];
    if (((struct Term*)tokenObj)->name == tokenType) {
        ++(*tokenIndex);
        *result = tokenObj;
        return true;
    }
    return false;
}

bool_t pStrip(struct Vector* tokens, index_t* tokenIndex, struct Object** result) {
    (void)tokens;
    (void)tokenIndex;
    *result = ((struct Term*)*result)->args[0];
    return true;
}

/* Private functions *********************************************************/

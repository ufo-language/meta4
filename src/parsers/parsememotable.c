#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/address.h"
#include "object/types/array.h"
#include "object/types/integer.h"
#include "object/types/vector.h"
#include "parsers/parser.h"
#include "parsers/parsememotable.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void parser_addRecursionBarrier(ParserFunction parserFunction, struct ParseState* parseState) {
    parser_memoizeResult(parseState->memoVector, parserFunction, parseState->index, PRS_Fail, (struct Object*)g_nil);
}

bool_t parser_memoLookup(struct Vector* memoVector,
                         ParserFunction parserFunction,
                         index_t tokenIndex,
                         enum ParseResultStatus* status,
                         struct Object** resultObj) {
    struct Object* entry = g_uniqueObject;
    if (vector_get(memoVector, tokenIndex, &entry) != SubscriptResult_OK) {
        return false;
    }
    /* Traverse the chain links in the bucket */
    while (entry != (struct Object*)g_nil) {
        /* Does key match? */
        struct Array* entryArray = (struct Array*)entry;
        struct Address* entryAddress = (struct Address*)entryArray->elems[0];
        if (((void*)parserFunction == entryAddress->address)) {
            *status = ((struct Integer*)entryArray->elems[1])->i;
            *resultObj = entryArray->elems[2];
            return true;
        }
        /* Move to next entry */
        entry = entryArray->elems[3];
    }
    return false;
}

void parser_memoizeResult(struct Vector* memoVector,
                          ParserFunction parserFunction,
                          index_t tokenIndex,
                          enum ParseResultStatus status,
                          struct Object* resultObj) {
    struct Object* nextResult;
    if (memoVector->nElems > tokenIndex) {
        nextResult = memoVector->elems->elems[tokenIndex];
    }
    else {
        nextResult = (struct Object*)g_nil;
    }
    struct Object* elems[] = {
        (struct Object*)address_new((void*)parserFunction),
        // (struct Object*)integer_new(tokenIndex),
        (struct Object*)integer_new(status),
        resultObj,
        nextResult
    };
    struct Array* resultArray = array_new_withElems(4, elems);
    vector_set_raw(memoVector, tokenIndex, (struct Object*)resultArray);
}

/* Private functions *********************************************************/

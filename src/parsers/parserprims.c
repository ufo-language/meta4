#include "_typedefs.h"

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
bool_t pSpot(struct Symbol* tokenType, struct Vector* tokens, index_t* tokenIndex, struct Vector* results) {
    struct Object* tokenObj = tokens->elems->elems[*tokenIndex];
    if (((struct Term*)tokenObj)->name == tokenType) {
        ++(*tokenIndex);
        vector_push(results, tokenObj);
        return true;
    }
    return false;
}

bool_t pStrip(struct Vector* tokens, index_t* tokenIndex, struct Vector* results) {
    (void)tokens;
    (void)tokenIndex;
#if 0
    struct Object* tokenObj = vector_pop_unsafe(results);
    struct Term* token = (struct Term*)tokenObj;
    struct Object* arg = token->args[0];
    vector_push(results, arg);
#else
    vector_push(results, ((struct Term*)vector_pop_unsafe(results))->args[0]);
#endif
    return true;
}

/* Private functions *********************************************************/

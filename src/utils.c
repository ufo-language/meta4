#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/memory.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

#if 0
string_t strdup(const string_t chars) {
    assert(chars);
    count_t nChars = strlen(chars) + 1;
    string_t newChars = memory_alloc(NBYTES_TO_WORDS(nChars));
    assert(newChars);
    memcpy(newChars, chars, nChars);
    return newChars;
}
#endif

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/globals.h"
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

/* Unique functions ******************/

struct Term* errorTerm0(const string_t name, const string_t message) {
    count_t nArgs = 1;
    struct Object* args[] = {(struct Object*)string_new(message)};
    return term_new(symbol_new(name), nArgs, args, (struct Object*)g_nil);
}

struct Term* errorTerm1(const string_t name, const string_t message, struct Object* arg) {
    count_t nArgs = 2;
    struct Object* args[] = {(struct Object*)string_new(message), arg};
    return term_new(symbol_new(name), nArgs, args, (struct Object*)g_nil);
}

/* Object functions ******************/

/* Private functions *********************************************************/

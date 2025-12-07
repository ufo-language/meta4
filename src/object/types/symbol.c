#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/evaluator/evaluator_recursive.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/symbol.h"
#include "object/types/string.h"
#include "object/types/vector.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* symbol_new(const string_t name) {
    return symbolic_new(name, OT_Symbol, g_symbolInternTable);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void symbol_show(struct Symbolic* symbol, FILE* stream) {
    fputs(symbol->name, stream);
}

/* Private functions *********************************************************/

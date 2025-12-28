#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/compare.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/outstream.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/symbolic.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbol* symbol_new(const string_t name) {
    return (struct Symbol*)symbolic_new(name, OT_Symbol, g_symbolInternTable);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

enum CompareResult symbol_compare(struct Symbol* symbol, struct Symbol* otherSymbol) {
    return string_compare_chars(symbol->name, otherSymbol->name);
}

/* Private functions *********************************************************/

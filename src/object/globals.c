#include "_typedefs.h"

#include "memory/gc.h"
#include "object/globals.h"
#include "object/types/boolean.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/nil.h"
#include "object/types/pair.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

struct Boolean*      g_false;
struct Boolean*      g_true;
struct FunctionRule* g_emptyFunctionRule;
struct GC*           g_gc;
struct Identifier*   g_idNil;
struct Nil*          g_nil;
struct Object*       g_uniqueObject;
struct Pair*         g_emptyPair;
struct Vector*       g_identifierInternTable;
struct Vector*       g_symbolInternTable;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_init(void) {
    /* Memory & GC first */
    g_gc = gc_new();
    g_identifierInternTable = vector_new();
    g_symbolInternTable = vector_new();
    /* Create constants next */
    g_true = boolean_new(true);
    g_false = boolean_new(false);
    g_idNil = identifier_new("nil");
    g_nil = nil_new();
    g_uniqueObject = object_new(OT_Null, NWORDS(*g_uniqueObject));
    /* Data structures come last */
    g_emptyPair = pair_new_empty();
    g_emptyFunctionRule = function_emptyRule();
}

/* Private functions *********************************************************/

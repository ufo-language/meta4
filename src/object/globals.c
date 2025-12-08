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

struct Boolean*    g_false;
struct Boolean*    g_true;
struct Function*   g_emptyFunction;
struct GC*         g_gc;
struct Identifier* g_idNil;
struct Nil*        g_nil;
struct Object*     g_uniqueObject;
struct Pair*       g_emptyPair;
struct Vector*     g_identifierInternTable;
struct Vector*     g_symbolInternTable;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_init(void) {
    /* Memory & GC first */
    g_gc = gc_new();
    /* Create constants next */
    g_true = boolean_new(true);
    g_false = boolean_new(false);
    g_idNil = identifier_new("nil");
    g_nil = nil_new();
    g_uniqueObject = object_new(OT_Null, 0);
    /* Data structures come last */
    g_emptyPair = pair_new_empty();
    g_emptyFunction = function_new_empty();
    g_identifierInternTable = vector_new();
    g_symbolInternTable = vector_new();
}

/* Private functions *********************************************************/

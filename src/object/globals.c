#include "_typedefs.h"

#include "memory/gc.h"
#include "object/globals.h"
#include "object/types/boolean.h"
#include "object/types/nil.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

struct Boolean* g_true;
struct Boolean* g_false;
struct GC* g_gc;
struct Nil* g_nil;
struct Vector* g_identifierInternTable;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_init(void) {
    /* Memory & GC first */
    g_gc = gc_new();
    /* Create constants next */
    g_true = boolean_new(true);
    g_false = boolean_new(false);
    g_nil = nil_new();
    /* Data structures come last */
    g_identifierInternTable = vector_new();
}

/* Private functions *********************************************************/

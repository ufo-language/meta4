#include "_typedefs.h"

#include "memory/gc.h"
#include "object/globals.h"
#include "object/types/nil.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

struct GC* g_gc;
struct Nil* g_nil;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_init(void) {
    /* Memory & GC first */
    g_gc = gc_new();
    /* Create constants next */
    g_nil = nil_new();
    /* Data structures come last */
}

/* Private functions *********************************************************/

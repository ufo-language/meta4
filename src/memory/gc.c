#include <stdlib.h>

#include "_typedefs.h"

#include "memory/gc.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct GC* gc_new(void) {
    struct GC* gc = (struct GC*)malloc(sizeof(*gc));
    // TODO initialize
    return gc;
}

void gc_free(struct GC* gc) {
    free(gc);
}

/* Public functions **********************************************************/

bool_t gc_doGC(struct GC* gc) {
    return false;
}

void gc_pushRoot(struct GC* gc, struct Object* obj) {
}

void gc_popRoot(struct GC* gc) {
}

void gc_popRoots(struct GC* gc, count_t nRoots) {
}

/* Private functions *********************************************************/

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
    /* TODO initialize */
    return gc;
}

void gc_free(struct GC* gc) {
    free(gc);
}

/* Public functions **********************************************************/

bool_t gc_doGC(struct GC* gc) {
    /* TODO */
    (void)gc;
    return false;
}

void gc_pushRoot(struct GC* gc, struct Object* obj) {
    /* TODO */
    (void)gc;
    (void)obj;
}

void gc_popRoot(struct GC* gc) {
    /* TODO */
    (void)gc;
}

void gc_popRoots(struct GC* gc, count_t nRoots) {
    /* TODO */
    (void)gc;
    (void)nRoots;
}

/* Private functions *********************************************************/

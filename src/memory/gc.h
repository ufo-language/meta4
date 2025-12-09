#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct GC {
};

struct Object;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct GC* gc_new(void);
void gc_free(struct GC* gc);

/* Public functions **********************************************************/

bool_t gc_doGC(struct GC* gc);
void gc_pushRoot(struct GC* gc, struct Object* obj);
void gc_popRoot(struct GC* gc);
void gc_popRoots(struct GC* gc, count_t nRoots);

/* Private functions *********************************************************/

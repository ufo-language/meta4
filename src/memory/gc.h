#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

#define DEFAULT_GC_THRESHOLD (1 << 10)
#define DEFAULT_ROOT_STACK_CAPACITY 256

/* Types *********************************************************************/

struct Object;
struct BumpAllocator;

struct GC {
    struct BumpAllocator* fromSpace;
    struct BumpAllocator* toSpace;
    struct Object** rootStack;
    count_t rootStackSize;
    count_t rootStackCapacity;
    struct Object*** permanentRoots;
    count_t nPermanentRoots;
    count_t permanentRootsCapacity;
    count_t gcThreshold;
    count_t allocatedSinceGC;
};

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
void gc_registerPermanentRoot(struct GC* gc, struct Object** rootPtr);
void gc_setThreshold(struct GC* gc, count_t threshold);
void gc_recordAllocation(struct GC* gc, count_t nWords);

/* Private functions *********************************************************/

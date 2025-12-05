#include <string.h>

#include "_typedefs.h"

#include "memory.h"
#include "memory/bumpallocator.h"

/*
    This file defines what kind of allocator to use.
*/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

struct BumpAllocator* g_bumpAllocator;

/* Lifecycle functions *******************************************************/

void memory_init(count_t nWords) {
    g_bumpAllocator = bumpAllocator_new(nWords);
}

void memory_free(void) {
    bumpAllocator_free(g_bumpAllocator);
}

/* Public functions **********************************************************/

address_t memory_alloc(count_t nWords) {
    return bumpAllocator_allocate(g_bumpAllocator, nWords);
}

address_t memory_realloc(address_t addr, count_t oldNWords, count_t newNWords) {
    return bumpAllocator_realloc(g_bumpAllocator, addr, oldNWords, newNWords);
}

void memory_restore(index_t index) {
    bumpAllocator_resotre(g_bumpAllocator, index);
}

index_t memory_save(void) {
    return bumpAllocator_save(g_bumpAllocator);
}

/* Private functions *********************************************************/

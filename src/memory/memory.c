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

#if 0
#include <stdio.h>
#include <stdlib.h>
#endif
address_t memory_alloc(count_t nWords) {
    #if 1
    return bumpAllocator_allocate(g_bumpAllocator, nWords);
    #elif 1
    address_t address = bumpAllocator_allocate(g_bumpAllocator, nWords);
    fprintf(stderr, "memory_alloc %2lu words / %2lu bytes @ %p - %p\n", nWords, (nWords * sizeof(word_t)), address, (void*)((intptr_t)address + (nWords * sizeof(word_t))));
    return address;
    #else  /* for valgrind */
    count_t nBytes = nWords * sizeof(word_t);
    address_t address = malloc(nBytes);
    fprintf(stderr, "malloced %lu bytes @ %p\n", nBytes, address);
    return address;
    #endif
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

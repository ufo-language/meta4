#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/bumpallocator_struct.h"
#include "memory/bumpallocator.h"
#include "memory/gc.h"
#include "memory/memory.h"
#include "object/globals.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* → struct BumpAllocator is in bumpallocator_struct.h */
/* for reference
struct BumpAllocator {
    count_t nWordsCapacity;
    index_t nextFree;
    word_t arena[];
};
*/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct BumpAllocator* bumpAllocator_new(count_t nWords) {
    struct BumpAllocator* bumpAllocator = malloc(sizeof(struct BumpAllocator) + nWords * sizeof(word_t));
    bumpAllocator_init(bumpAllocator, nWords);
    return bumpAllocator;
}

void bumpAllocator_init(struct BumpAllocator* bumpAllocator, count_t nWords) {
    bumpAllocator->nWordsCapacity = nWords;
    bumpAllocator->nextFree = 0;
}

void bumpAllocator_free(struct BumpAllocator* bumpAllocator) {
    free(bumpAllocator);
}

/* Public functions **********************************************************/

address_t bumpAllocator_allocate(struct BumpAllocator* allocator, count_t nWords) {
    struct BumpAllocator* bumpAllocator = (struct BumpAllocator*)allocator;
    if (bumpAllocator->nextFree + nWords > bumpAllocator->nWordsCapacity) {
        if (!gc_doGC(g_gc)) {
            fprintf(stderr, "\nFATAL ERROR\nBumpAllocator out of memory allocating %lu words\n"
                "  nextFree = %lu\n  capacity = %lu\n",
                nWords, bumpAllocator->nextFree, bumpAllocator->nWordsCapacity);
            assert(false);
            exit(1);
        }
    }
    index_t objIndex = bumpAllocator->nextFree;
    bumpAllocator->nextFree += nWords;
    address_t address = &bumpAllocator->arena[objIndex];
    return address;
}

address_t bumpAllocator_realloc(struct BumpAllocator* allocator, address_t addr, count_t oldNWords, count_t newNWords) {
    struct BumpAllocator* bump = allocator;
    word_t* base = bump->arena;
    word_t* oldPtr = (word_t*)addr;
    index_t oldIndex = oldPtr - base;
    /* Case 1: In-place grow/shrink if top of vector */
    if (oldIndex + oldNWords == bump->nextFree) {
        if (oldIndex + newNWords > bump->nWordsCapacity) {
            fprintf(stderr,
                "\nFATAL ERROR\nBumpAllocator out of memory reallocating %lu→%lu words\n"
                "  nextFree = %lu\n  capacity = %lu\n",
                oldNWords, newNWords, bump->nextFree, bump->nWordsCapacity);
            exit(1);
        }
        bump->nextFree = oldIndex + newNWords;
        return addr;  /* same pointer */
    }
    /* Case 2: Allocate a new block */
    address_t newAddr = bumpAllocator_allocate(bump, newNWords);
    word_t* out = (word_t*)newAddr;
    /* Number of 64-bit words to copy */
    count_t count = oldNWords < newNWords ? oldNWords : newNWords;
    /* Fast 64-bit copy */
    if (count <= 8) {
        /* Manual unroll for very small copies (avoids memcpy call overhead) */
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wimplicit-fallthrough"
        switch (count) {
            case 8: out[7] = oldPtr[7];
            case 7: out[6] = oldPtr[6];
            case 6: out[5] = oldPtr[5];
            case 5: out[4] = oldPtr[4];
            case 4: out[3] = oldPtr[3];
            case 3: out[2] = oldPtr[2];
            case 2: out[1] = oldPtr[1];
            case 1: out[0] = oldPtr[0];
            default: break;
        }
        #pragma clang diagnostic pop
    }
    else {
        /* Larger blocks use memcpy (optimized through movsq or AVX) */
        memcpy(out, oldPtr, count * sizeof(word_t));
    }
    return newAddr;
}

void bumpAllocator_resotre(struct BumpAllocator* bumpAllocator, index_t index) {
    bumpAllocator->nextFree = index;
}

index_t bumpAllocator_save(struct BumpAllocator* bumpAllocator) {
    return bumpAllocator->nextFree;
}

/* Private functions *********************************************************/

#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct BumpAllocator;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct BumpAllocator* bumpAllocator_new(count_t nWords);
void bumpAllocator_init(struct BumpAllocator* bumpAllocator, count_t nWords);
void bumpAllocator_free(struct BumpAllocator* bumpAllocator);

/* Public functions **********************************************************/

address_t bumpAllocator_allocate(struct BumpAllocator* allocator, count_t nWords);
address_t bumpAllocator_realloc(struct BumpAllocator* allocator, address_t addr, count_t oldNWords, count_t newNWords);
void bumpAllocator_resotre(struct BumpAllocator* bumpAllocator, index_t index);
index_t bumpAllocator_save(struct BumpAllocator* bumpAllocator);

/* Private functions *********************************************************/

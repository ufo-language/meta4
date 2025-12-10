#pragma once

#include "_typedefs.h"

#include "memory/bumpallocator.h"

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

#define DEFAULT_HEAP_SIZE 1<<12  /* 4096 words, or 32kB */

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

void memory_init(count_t nWords);
void memory_free(void);

/* Public functions **********************************************************/

address_t memory_alloc(count_t nWords);
void memory_restore(index_t index);
address_t memory_realloc(address_t addr, count_t existingCapacity, count_t newCapacity);
index_t memory_save(void);

/* Private functions *********************************************************/

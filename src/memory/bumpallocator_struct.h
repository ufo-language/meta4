#pragma once

#include "_typedefs.h"

#include "memory/memory.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct BumpAllocator {
    count_t nWordsCapacity;
    index_t nextFree;
    word_t arena[];
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Private functions *********************************************************/

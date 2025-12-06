#pragma once

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/intarray.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct IntVector {
    struct Object obj;
    count_t top;
    count_t capacity;
    count_t nResizes;
    struct IntArray* elems;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntVector* intVector_new(void);
struct IntVector* intVector_new_withCapacity(count_t capacity);

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t intVector_get(struct IntVector* intVector, index_t index, int_t* elem);
bool_t intVector_set(struct IntVector* intVector, index_t index, int_t elem);
bool_t intVector_pop(struct IntVector* intVector, int_t* elem);
void intVector_push(struct IntVector* intVector, int_t elem);

/* Object functions ******************/

count_t intVector_count(struct IntVector* intVector);
void intVector_show(struct IntVector* intVector, FILE* stream);

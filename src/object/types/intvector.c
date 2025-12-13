#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/intvector.h"

/* Defines *******************************************************************/

#define DEFAULT_STACK_SIZE 8

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _resize(struct IntVector* intVector);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntVector* intVector_new(void) {
    return intVector_new_withCapacity(DEFAULT_STACK_SIZE);
}

struct IntVector* intVector_new_withCapacity(count_t capacity) {
    struct IntVector* intVector = (struct IntVector*)object_new(OT_IntVector, NWORDS(*intVector));
    intVector->top = 0;
    intVector->capacity = capacity;
    intVector->elems = intArray_new_noFill(capacity);
    intVector->nResizes = 0;
    return intVector;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t intVector_get(struct IntVector* intVector, index_t index, int_t* elem) {
    if (index >= intVector->top) {
        return false;
    }
    *elem = intArray_get_unsafe(intVector->elems, index);
    return true;
}

bool_t intVector_set(struct IntVector* intVector, index_t index, int_t elem) {
    if (index >= intVector->top) {
        return false;
    }
    intArray_set_unsafe(intVector->elems, index, elem);
    return true;
}

bool_t intVector_pop(struct IntVector* intVector, int_t* elem) {
    if (intVector->top == 0) {
        return false;
    }
    *elem = intVector->elems->elems[--intVector->top];
    return true;
}

void intVector_push(struct IntVector* intVector, int_t elem) {
    if (intVector->top == intVector->elems->nElems) {
        _resize(intVector);
    }
    intVector->elems->elems[intVector->top++] = elem;
}

/* Object functions ******************/

count_t intVector_count(struct IntVector* intVector) {
    return intVector->top;
}

void intVector_show(struct IntVector* intVector, FILE* stream) {
    fputs("{%|", stream);
    int_t* elems = intVector->elems->elems;
    for (index_t n=0; n<intVector->top; ++n) {
        if (n > 0) {
            fputs(", ", stream);
        }
        fprintf(stream, "%ld", elems[n]);
    }
    fputs("|}", stream);
}

/* Private functions *********************************************************/

static void _resize(struct IntVector* intVector) {
    intVector->capacity *= 2;
    struct IntArray* newElems = intArray_new_fromIntArray(intVector->capacity, intVector->elems);
    intVector->elems = newElems;
    ++intVector->nResizes;
}

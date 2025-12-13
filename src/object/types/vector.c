#include <assert.h>
#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/vector.h"
#include "object/functions/equal.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

#define DEFAULT_STACK_SIZE 8

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _vector_resize(struct Vector* vector);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Vector* vector_new(void) {
    return vector_new_withCapacity(DEFAULT_STACK_SIZE);
}

struct Vector* vector_new_withCapacity(count_t capacity) {
    struct Vector* vector = (struct Vector*)object_new(OT_Vector, NWORDS(*vector));
    vector->top = 0;
    // vector->capacity = capacity;
    vector->elems = array_new_noFill(capacity);
    vector->nResizes = 0;
    return vector;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

count_t vector_capacity(struct Vector* vector) {
    return vector->elems->nElems;
}

index_t vector_top(struct Vector* vector) {
    return vector->top;
}

void vector_setTop(struct Vector* vector, index_t newTop) {
    assert(newTop <= vector->top);
    vector->top = newTop;
}

void vector_bindPair(struct Vector* vector, struct Object* key, struct Object* value) {
    vector_push(vector, key);
    vector_push(vector, value);
}

/* This treats the array as an association list of pairs: [key, value, key, value...] */
bool_t vector_lookup(struct Vector* vector, struct Object* key, struct Object** value) {
    return array_lookupElems(vector->top, vector->elems->elems, key, value);
}

bool_t vector_get(struct Vector* vector, index_t index, struct Object** elem) {
    if (index >= vector->top) {
        return false;
    }
    *elem = vector->elems->elems[index];
    return true;
}

bool_t vector_set(struct Vector* vector, index_t index, struct Object* elem) {
    if (index >= vector->top) {
        return false;
    }
    vector->elems->elems[index] = elem;
    return true;
}

bool_t vector_pop(struct Vector* vector, struct Object** elem) {
    if (vector->top == 0) {
        return false;
    }
    *elem = vector->elems->elems[--vector->top];
    return true;
}

void vector_push(struct Vector* vector, struct Object* elem) {
    if (vector->top == vector->elems->nElems) {
        _vector_resize(vector);
    }
    vector->elems->elems[vector->top++] = elem;
}

void vector_showBindings(struct Vector* vector, FILE* stream) {
    array_showBindings(vector->top, vector->elems->elems, "(|", ", ", "|}", stream);
}

/* Object functions ******************/

count_t vector_count(struct Vector* vector) {
    return vector->top;
}

void vector_show(struct Vector* vector, FILE* stream) {
    array_showElems(vector->top, vector->elems->elems, "(|", ", ", "|}", stream);
}

/* Private functions *********************************************************/

static void _vector_resize(struct Vector* vector) {
    count_t nElems = vector->elems->nElems;
    struct Array* newElems = array_new_noFill(nElems * 2);
    array_init(newElems, nElems, vector->elems->elems);
    vector->elems = newElems;
    ++vector->nResizes;
}

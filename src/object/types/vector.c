#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/vector.h"
#include "object/functions/equal.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

#define DEFAULT_STACK_SIZE 8

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _resize(struct Vector* vector);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Vector* vector_new(void) {
    return vector_new_withCapacity(DEFAULT_STACK_SIZE);
}

struct Vector* vector_new_withCapacity(count_t capacity) {
    struct Vector* vector = (struct Vector*)object_new(OT_Vector, NWORDS(*vector));
    vector->top = 0;
    vector->capacity = capacity;
    vector->elems = array_new_noFill(capacity);
    vector->nResizes = 0;
    return vector;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* This treats the vector as an association list of [key, value, key, value...] */
bool_t vector_lookup(struct Vector* vector, struct Object* key, struct Object** value) {
    struct Object** elems = vector->elems->elems;
    count_t top = vector->top;
    for (index_t n=0; n<top; n+=2) {
        if (equal(elems[n], key)) {
            *value = elems[n+1];
            return true;
        }
    }
    return false;
}

bool_t vector_get(struct Vector* vector, index_t index, struct Object** elem) {
    if (index >= vector->top) {
        return false;
    }
    *elem = array_get_unsafe(vector->elems, index);
    return true;
}

bool_t vector_set(struct Vector* vector, index_t index, struct Object* elem) {
    if (index >= vector->top) {
        return false;
    }
    array_set_unsafe(vector->elems, index, elem);
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
        _resize(vector);
    }
    vector->elems->elems[vector->top++] = elem;
}

/* Object functions ******************/

count_t vector_count(struct Vector* vector) {
    return vector->top;
}

void vector_show(struct Vector* vector, FILE* stream) {
    fputs("{|", stream);
    index_t index = vector->top - 1;
    struct Object** elems = vector->elems->elems;
    for (index_t n=0; n<vector->top; ++n) {
        if (n > 0) {
            fputs(", ", stream);
        }
        show(elems[index--], stream);
    }
    fputs("|}", stream);
}

/* Private functions *********************************************************/

static void _resize(struct Vector* vector) {
    vector->capacity *= 2;
    struct Array* newElems = array_new_fromArray(vector->capacity, vector->elems);
    vector->elems = newElems;
    ++vector->nResizes;
}

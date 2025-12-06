#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/vector.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

#define DEFAULT_STACK_SIZE 8

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void _resize(struct Vector* vector);

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

bool_t vector_get(struct Vector* vector, index_t index, struct Object** value) {
    if (index >= vector->top) {
        return false;
    }
    *value = array_get_unsafe(vector->elems, index);
    return true;
}

bool_t vector_set(struct Vector* vector, index_t index, struct Object* value) {
    if (index >= vector->top) {
        return false;
    }
    array_set_unsafe(vector->elems, index, value);
    return true;
}

bool_t vector_pop(struct Vector* vector, struct Object** value) {
    if (vector->top == 0) {
        return false;
    }
    *value = vector->elems->elems[--vector->top];
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

void _resize(struct Vector* vector) {
    vector->capacity *= 2;
    struct Array* newElems = array_new_fromArray(vector->capacity, vector->elems);
    vector->elems = newElems;
    ++vector->nResizes;
}

#include <assert.h>
#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/integer.h"
#include "object/types/outstream.h"
#include "object/types/subscript.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

#define VECTOR_OPEN "{|"
#define VECTOR_CLOSE "|}"

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _vector_resize(struct Vector* vector);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Vector* vector_new(void) {
    return vector_new_withCapacity(DEFAULT_VECTOR_CAPACITY);
}

struct Vector* vector_new_withCapacity(count_t capacity) {
    struct Vector* vector = (struct Vector*)object_new(OT_Vector, NWORDS(*vector));
    vector->nElems = 0;
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

void vector_clear(struct Vector* vector) {
    vector->nElems = 0;
}

void vector_bindPair(struct Vector* vector, struct Object* key, struct Object* value) {
    vector_push(vector, key);
    vector_push(vector, value);
}

/* This treats the array as an association list of pairs: [key, value, key, value...] */
bool_t vector_locate(struct Vector* vector, struct Object* key, int_t* index) {
    return array_locate_usingElems(vector->nElems, vector->elems->elems, key, index);
}

/* This treats the array as an association list of pairs: [key, value, key, value...] */
bool_t vector_lookup(struct Vector* vector, struct Object* key, struct Object** value) {
    return array_lookup_usingElems(vector->nElems, vector->elems->elems, key, value);
}

enum SubscriptResult vector_get(struct Vector* vector, index_t index, struct Object** elem) {
    if (index >= vector->nElems) {
        return SubscriptResult_IndexOutOfBounds;
    }
    *elem = vector->elems->elems[index];
    return SubscriptResult_OK;
}

bool_t vector_pop(struct Vector* vector, struct Object** elem) {
    if (vector->nElems == 0) {
        return false;
    }
    *elem = vector->elems->elems[--vector->nElems];
    return true;
}

void vector_push(struct Vector* vector, struct Object* elem) {
    if (vector->nElems == vector->elems->nElems) {
        _vector_resize(vector);
    }
    vector->elems->elems[vector->nElems++] = elem;
}

/* This treats the array as an association list of pairs: [key, value, key, value...] */
bool_t vector_rebind(struct Vector* vector, struct Object* key, struct Object* value) {
    int_t index;
    if (vector_locate(vector, key, &index)) {
        vector_set_raw(vector, index, value);
        return true;
    }
    return false;
}

enum SubscriptResult vector_set(struct Vector* vector, struct Object* indexObj, struct Object* elem) {
    if (indexObj->typeId != OT_Integer) {
        return SubscriptResult_IndexType;
    }
    int_t indexInt = ((struct Integer*)indexObj)->i;
    if (indexInt < 0) {
        return SubscriptResult_IndexOutOfBounds;
    }
    index_t index = (index_t)indexInt;
    vector_set_raw(vector, index, elem);
    return SubscriptResult_OK;
}

void vector_set_raw(struct Vector* vector, index_t index, struct Object* elem) {
    if (index >= vector->nElems) {
        while (vector->elems->nElems <= index) {
            _vector_resize(vector);
        }
        struct Object** elems = vector->elems->elems;
        for (index_t n=vector->nElems; n<index; n++) {
            elems[n] = (struct Object*)g_nil;
        }
        vector->nElems = index + 1;
    }
    vector->elems->elems[index] = elem;
}

void vector_showBindings(struct Vector* vector, struct OutStream* outStream) {
    array_showBindings(vector->nElems, vector->elems->elems, VECTOR_OPEN, ", ", VECTOR_CLOSE, outStream);
}

index_t vector_top(struct Vector* vector) {
    return vector->nElems;
}

void vector_setTop(struct Vector* vector, index_t newTop) {
    assert(newTop <= vector->nElems);
    vector->nElems = newTop;
}

/* Object functions ******************/

count_t vector_count(struct Vector* vector) {
    return vector->nElems;
}

void vector_show(struct Vector* vector, struct OutStream* outStream) {
    array_show_usingElems(vector->nElems, vector->elems->elems, VECTOR_OPEN, ", ", VECTOR_CLOSE, outStream);
}

/* Private functions *********************************************************/

static void _vector_resize(struct Vector* vector) {
    count_t nElems = vector->elems->nElems;
    struct Array* newElems = array_new_noFill(nElems * 2);
    array_init(newElems, nElems, vector->elems->elems);
    vector->elems = newElems;
    ++vector->nResizes;
}

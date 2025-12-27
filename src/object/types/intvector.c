#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/integer.h"
#include "object/types/intvector.h"
#include "object/types/outstream.h"
#include "object/errorterm.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _intVector_resize(struct IntVector* intVector);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntVector* intVector_new(void) {
    return intVector_new_withCapacity(DEFAULT_INTVECTOR_CAPACITY);
}

struct IntVector* intVector_new_withCapacity(count_t capacity) {
    struct IntVector* intVector = (struct IntVector*)object_new(OT_IntVector, NWORDS(*intVector));
    intVector->nElems = 0;
    intVector->capacity = capacity;
    intVector->elems = intArray_new_noFill(capacity);
    intVector->nResizes = 0;
    return intVector;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t intVector_get(struct IntVector* intVector, index_t index, int_t* elem) {
    if (index >= intVector->nElems) {
        return false;
    }
    *elem = intArray_get_unsafe(intVector->elems, index);
    return true;
}

#if 0
bool_t intVector_set(struct IntVector* intVector, index_t index, int_t elem) {
    if (index >= intVector->nElems) {
        return false;
    }
    intArray_set_unsafe(intVector->elems, index, elem);
    return true;
}
#endif

bool_t intVector_set(struct IntVector* intVector, struct Object* indexObj, struct Object* elemObj, struct Object** error) {
    if (indexObj->typeId != OT_Integer) {
        *error = (struct Object*)errorTerm1("IntVector", "Index must be an Integer", indexObj);
        return false;
    }
    int_t indexInt = ((struct Integer*)indexObj)->i;
    if (indexInt < 0) {
        *error = (struct Object*)errorTerm1("IntVector", "Index can't be negative", indexObj);
        return false;
    }
    index_t index = (index_t)indexInt;
    if (index >= intVector->nElems) {
        *error = (struct Object*)errorTerm1("IntVector", "Index is too large", indexObj);
        return false;
    }
    if (elemObj->typeId != OT_Integer) {
        *error = (struct Object*)errorTerm1("IntVector", "Element value must be an Integer", elemObj);
        return false;
    }
    int_t elem = ((struct Integer*)elemObj)->i;
    intVector->elems->elems[index] = elem;
    return true;
}

bool_t intVector_pop(struct IntVector* intVector, int_t* elem) {
    if (intVector->nElems == 0) {
        return false;
    }
    *elem = intVector->elems->elems[--intVector->nElems];
    return true;
}

void intVector_push(struct IntVector* intVector, int_t elem) {
    if (intVector->nElems == intVector->elems->nElems) {
        _intVector_resize(intVector);
    }
    intVector->elems->elems[intVector->nElems++] = elem;
}

/* Object functions ******************/

count_t intVector_count(struct IntVector* intVector) {
    return intVector->nElems;
}

void intVector_show(struct IntVector* intVector, struct OutStream* outStream) {
    outStream_writeString(outStream, "{i|");
    int_t* elems = intVector->elems->elems;
    for (index_t n=0; n<intVector->nElems; ++n) {
        if (n > 0) {
            outStream_writeString(outStream, ", ");
        }
        outStream_writeUInt(outStream, elems[n]);
    }
    outStream_writeString(outStream, "|}");
}

/* Private functions *********************************************************/

static void _intVector_resize(struct IntVector* intVector) {
    intVector->capacity *= 2;
    struct IntArray* newElems = intArray_new_fromIntArray(intVector->capacity, intVector->elems);
    intVector->elems = newElems;
    ++intVector->nResizes;
}

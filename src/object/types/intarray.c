#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/intarray.h"
#include "object/types/integer.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntArray* intArray_new3(int i1, int i2, int i3) {
    struct IntArray* intArray = intArray_new_noFill(3);
    intArray->elems[0] = i1;
    intArray->elems[1] = i2;
    intArray->elems[2] = i3;
    return intArray;
}

struct IntArray* intArray_new_elem(count_t nElems, int_t elem) {
    struct IntArray* intArray = intArray_new_noFill(nElems);
    for (index_t n=0; n<nElems; ++n) {
        intArray->elems[n] = elem;
    }
    return intArray;
}

struct IntArray* intArray_new_elems(count_t nElems, int_t elems[]) {
    struct IntArray* intArray = intArray_new_noFill(nElems);
    memcpy(intArray->elems, elems, sizeof(struct Object*) * nElems);
    return intArray;
}

struct IntArray* intArray_new_fromIntArray(count_t nElems, struct IntArray* oldArray) {
    struct IntArray* intArray = intArray_new_noFill(nElems);
    if (nElems > oldArray->nElems) {
        nElems = oldArray->nElems;
    }
    for (index_t n=0; n<nElems; ++n) {
        intArray->elems[n] = oldArray->elems[n];
    }
    return intArray;
}

struct IntArray* intArray_new_noFill(count_t nElems) {
    struct IntArray* intArray = (struct IntArray*)object_new(OT_IntArray, NWORDS(*intArray) + nElems);
    intArray->nElems = nElems;
    return intArray;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

int_t intArray_get_unsafe(struct IntArray* intArray, index_t index) {
    return intArray->elems[index];
}

bool_t intArray_set(struct IntArray* intArray, struct Object* indexObj, struct Object* elemObj, struct Object** error) {
    if (indexObj->typeId != OT_Integer) {
        *error = (struct Object*)errorTerm_objAndType("IntArrayError", "Index must be an Integer", indexObj);
        return false;
    }
    int_t indexInt = ((struct Integer*)indexObj)->i;
    if (indexInt < 0) {
        *error = (struct Object*)errorTerm1("IntArrayError", "Index can't be negative", indexObj);
        return false;
    }
    index_t index = (index_t)indexInt;
    if (index >= intArray->nElems) {
        *error = (struct Object*)errorTerm1("IntArrayError", "Index is too large", indexObj);
        return false;
    }
    if (elemObj->typeId != OT_Integer) {
        *error = (struct Object*)errorTerm_objAndType("IntArrayError", "Element value must be an Integer", elemObj);
        return false;
    }
    int_t elem = ((struct Integer*)elemObj)->i;
    intArray->elems[index] = elem;
    return true;
}

void intArray_set_unsafe(struct IntArray* intArray, index_t index, int_t elem) {
    intArray->elems[index] = elem;
}

/* Object functions ******************/

void intArray_show(struct IntArray* intArray, struct OutStream* outStream) {
    outStream_writeString(outStream, "IntArray{");
    for (index_t n=0; n<intArray->nElems; ++n) {
        if (n > 0) {
            outStream_writeString(outStream, ", ");
        }
        outStream_writeInt(outStream, intArray->elems[n]);
    }
    outStream_writeChar(outStream, '}');
}

/* Private functions *********************************************************/

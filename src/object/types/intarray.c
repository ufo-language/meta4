#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/intarray.h"
#include "object/typeids.h"

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

void intArray_set_unsafe(struct IntArray* intArray, index_t index, int_t elem) {
    intArray->elems[index] = elem;
}

/* Object functions ******************/

void intArray_show(struct IntArray* intArray, FILE* stream) {
    fputs("IntArray{", stream);
    for (index_t n=0; n<intArray->nElems; ++n) {
        if (n > 0) {
            fputs(", ", stream);
        }
        fprintf(stream, "%ld", intArray->elems[n]);
    }
    fputc('}', stream);
}

/* Private functions *********************************************************/

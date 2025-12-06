#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/types/intarray.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

#include <assert.h>


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

struct IntArray* intArray_new_noFill(count_t nElems) {
    struct IntArray* intArray = (struct IntArray*)object_new(OT_IntArray, NWORDS(*intArray) + nElems);
    intArray->nElems = nElems;
    return intArray;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

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

#include <string.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/array.h"
#include "object/functions/eval.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Array* array_new_elem(count_t nElems, struct Object* elem) {
    struct Array* array = array_new_noFill(nElems);
    for (index_t n=0; n<nElems; ++n) {
        array->elems[n] = elem;
    }
    return array;
}

struct Array* array_new_elems(count_t nElems, struct Object* elems[]) {
    struct Array* array = array_new_noFill(nElems);
    memcpy(array->elems, elems, sizeof(struct Object*) * nElems);
    return array;
}

struct Array* array_new_fromArray(count_t nElems, struct Array* oldArray) {
    struct Array* array = array_new_noFill(nElems);
    if (nElems > oldArray->nElems) {
        nElems = oldArray->nElems;
    }
    for (index_t n=0; n<nElems; ++n) {
        array->elems[n] = oldArray->elems[n];
    }
    return array;
}

struct Array* array_new_noFill(count_t nElems) {
    struct Array* array = (struct Array*)object_new(OT_Array, NWORDS(struct Array) + nElems);
    array->nElems = nElems;
    return array;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

struct Object* array_get_unsafe(struct Array* array, index_t index) {
    return array->elems[index];
}

void array_set_unsafe(struct Array* array, index_t index, struct Object* value) {
    array->elems[index] = value;
}

/* Object functions ******************/

bool_t array_eval(struct Array* array, struct Evaluator* etor, struct Object** value) {
    count_t nElems = array->nElems;
    struct Array* newArray = array_new_noFill(nElems);
    struct Object** elems = array->elems;
    struct Object** newElems = array->elems;
    struct Object* value1;
    for (index_t n=0; n<nElems; ++n) {
        if (eval(elems[n], etor, &value1)) {
            newElems[n] = value1;
        }
        else {
            return false;
        }
    }
    *value = (struct Object*)newArray;
    return true;
}

void array_show(struct Array* array, FILE* stream) {
    fputc('{', stream);
    array_showElemsWith(array->nElems, array->elems, ", ", stream);
    fputc('}', stream);
}

void array_showElemsWith(count_t nElems, struct Object* elems[], const string_t sep, FILE* stream) {
    for (index_t n=0; n<nElems; ++n) {
        if (n > 0) {
            fputs(sep, stream);
        }
        show(elems[n], stream);
    }
}

/* Private functions *********************************************************/

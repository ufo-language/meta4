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

struct Array* array_new(count_t nElems, struct Object* elems[]) {
    struct Array* array = (struct Array*)object_new(OT_Array, NWORDS(struct Array) + nElems);
    array_init(array, nElems, elems);
    return array;
}

/*
struct Array* array_new_fill(count_t nElems, struct Object* elem) {
    struct Array* array = (struct Array*)object_new(OT_Array, NWORDS(struct Array) + nElems);
    array->nElems = nElems;
    for (index_t n=0; n<nElems; ++n) {
        array->elems[n] = elem;
    }
    return array;
}
*/

struct Array* array_new_nofill(count_t nElems) {
    struct Array* array = (struct Array*)object_new(OT_Array, NWORDS(struct Array) + nElems);
    array->nElems = nElems;
    return array;
}

void array_init(struct Array* array, count_t nElems, struct Object* elems[]) {
    array->nElems = nElems;
    memcpy(array->elems, elems, sizeof(struct Object*) * nElems);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t array_eval(struct Array* array, struct Evaluator* etor, struct Object** value) {
    count_t nElems = array->nElems;
    struct Array* newArray = array_new_nofill(nElems);
    struct Object** elems = array->elems;
    struct Object** newElems = array->elems;
    struct Object* value1;
    for (index_t n=0; n<nElems; n++) {
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
    for (index_t n=0; n<nElems; n++) {
        if (n > 0) {
            fputs(sep, stream);
        }
        show(elems[n], stream);
    }
}

/* Private functions *********************************************************/

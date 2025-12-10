#include <string.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/array.h"
#include "object/functions/close_rec.h"
#include "object/functions/equal.h"
#include "object/functions/eval_rec.h"
#include "object/functions/match.h"
#include "object/functions/show.h"
#include "object/types/vector.h"

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

bool_t array_closeElems_rec(count_t nElems, struct Object* elems[], struct Object* newElems[], struct Etor_rec* etor, struct Object** error) {
    struct Object* value;
    for (index_t n=0; n<nElems; n++) {
        if (!close_rec(elems[n], etor, &value)) {
            *error = value;
            return false;
        }
        newElems[n] = value;
    }
    return true;
}

bool_t array_evalElems_rec(count_t nElems, struct Object* elems[], struct Object* newElems[], struct Etor_rec* etor, struct Object** error) {
    struct Object* value;
    for (index_t n=0; n<nElems; n++) {
        if (!eval_rec(elems[n], etor, &value)) {
            *error = value;
            return false;
        }
        newElems[n] = value;
    }
    return true;
}

void array_showElems(count_t nElems, struct Object* elems[], const string_t sep, FILE* stream) {
    for (index_t n=0; n<nElems; ++n) {
        if (n > 0) {
            fputs(sep, stream);
        }
        show(elems[n], stream);
    }
}

/* Object functions ******************/

bool_t array_close_rec(struct Array* array, struct Etor_rec* etor, struct Object** value) {
    struct Array* newArray = array_new_noFill(array->nElems);
    if (!array_closeElems_rec(array->nElems, array->elems, newArray->elems, etor, value)) {
        return false;
    }
    *value = (struct Object*)newArray;
    return true;
}

bool_t array_eval_rec(struct Array* array, struct Etor_rec* etor, struct Object** value) {
    struct Array* newArray = array_new_noFill(array->nElems);
    if (!array_evalElems_rec(array->nElems, array->elems, newArray->elems, etor, value)) {
        return false;
    }
    *value = (struct Object*)newArray;
    return true;
}

bool_t array_match(struct Array* array, struct Array* other, struct Vector* bindings) {
    if (array->nElems != other->nElems) {
        return false;
    }
    index_t savedTop = vector_top(bindings);
    for (index_t n=0; n<array->nElems; n++) {
        if (!match(array->elems[n], other->elems[n], bindings)) {
            vector_setTop(bindings, savedTop);
            return false;
        }
    }
    return true;
}

void array_show(struct Array* array, FILE* stream) {
    fputc('{', stream);
    array_showElems(array->nElems, array->elems, ", ", stream);
    fputc('}', stream);
}

/* Private functions *********************************************************/

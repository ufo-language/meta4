#include <math.h>
#include <string.h>

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/functions/close_rec.h"
#include "object/functions/compare.h"
#include "object/functions/eval_rec.h"
#include "object/functions/match.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/integer.h"
#include "object/types/outstream.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Array* array_new_withElem(count_t nElems, struct Object* elem) {
    struct Array* array = array_new_noFill(nElems);
    for (index_t n=0; n<nElems; ++n) {
        array->elems[n] = elem;
    }
    return array;
}

struct Array* array_new_withElems(count_t nElems, struct Object* elems[]) {
    struct Array* array = array_new_noFill(nElems);
    memcpy(array->elems, elems, sizeof(struct Object*) * nElems);
    return array;
}

struct Array* array_new_noFill(count_t nElems) {
    struct Array* array = (struct Array*)object_new(OT_Array, NWORDS(struct Array) + nElems);
    array->nElems = nElems;
    return array;
}

void array_init(struct Array* array, count_t nElems, struct Object* elems[]) {
    memcpy(array->elems, elems, sizeof(struct Object*) * nElems);
}

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t array_get(struct Array* array, struct Object* indexObj, struct Object** value) {
    switch (indexObj->typeId) {
        case OT_Integer:
            return array_get_index_t(array, ((struct Integer*)indexObj)->i, value);
        default:
            if (indexObj->typeId < OT_ConstantLimit) {
                return array_lookup_usingElems(array->nElems, array->elems, indexObj, value);
            }
            *value = (struct Object*)errorTerm1("ArrayError", "Unable to use object as array subscript index", indexObj);
            return false;
    }
}

bool_t array_get_index_t(struct Array* array, index_t index, struct Object** value) {
    if (index >= array->nElems) {
        *value = (struct Object*)errorTerm1("ArrayError", "Index out of bounds", (struct Object*)integer_new(index));
        return false;
    }
    *value = array->elems[index];
    return true;
}

bool_t array_set(struct Array* array, struct Object* indexObj, struct Object* value, struct Object** error) {
    switch (indexObj->typeId) {
        case OT_Integer:
            return array_set_index_t(array, ((struct Integer*)indexObj)->i, value, error);
        default:
            *error = (struct Object*)errorTerm1("ArrayError", "Unable to use object as array subscript index", indexObj);
            return false;
    }
}

bool_t array_set_index_t(struct Array* array, index_t index, struct Object* value, struct Object** error) {
    if (index >= array->nElems) {
        *error = (struct Object*)errorTerm1("ArrayError", "Index out of bounds", (struct Object*)integer_new(index));
        return false;
    }
    array->elems[index] = value;
    return true;
}

/* Element/array-wise operations; also used by other types */

void array_close_rec_usingElems(count_t nElems, struct Object* elems[], struct Object* newElems[], struct Etor_rec* etor) {
    for (index_t n=0; n<nElems; ++n) {
        newElems[n] = close_rec(elems[n], etor);
    }
}

bool_t array_eval_rec_usingElems(count_t nElems, struct Object* elems[], struct Object* newElems[], struct Etor_rec* etor, struct Object** error) {
    struct Object* value;
    for (index_t n=0; n<nElems; ++n) {
        if (!eval_rec(elems[n], etor, &value)) {
            *error = value;
            return false;
        }
        newElems[n] = value;
    }
    return true;
}

/* This treats the array as an association list of pairs: [key, value, key, value...] */
bool_t array_locate_usingElems(count_t nElems, struct Object* elems[], struct Object* key, int_t* index) {
    for (index_t n=0; n<nElems; n+=2) {
        if (compare(elems[n], key) == CompareEqual) {
            *index = n+1;
            return true;
        }
    }
    return false;
}

/* This treats the array as an association list of pairs: [key, value, key, value...] */
bool_t array_lookup_usingElems(count_t nElems, struct Object* elems[], struct Object* key, struct Object** value) {
    for (index_t n=0; n<nElems; n+=2) {
        if (compare(elems[n], key) == CompareEqual) {
            *value = elems[n+1];
            return true;
        }
    }
    *value = (struct Object*)errorTerm1("ArrayError", "Key not found in array", key);
    return false;
}

bool_t array_match_usingElems(count_t nElems, struct Object* elems[], struct Object* otherElems[], struct Vector* bindings) {
    index_t savedTop = vector_top(bindings);
    for (index_t n=0; n<nElems; ++n) {
        if (!match(elems[n], otherElems[n], bindings)) {
            vector_setTop(bindings, savedTop);
            return false;
        }
    }
    return true;
}

void array_show_usingElems(count_t nElems, struct Object* elems[], const string_t open, const string_t sep, const string_t close, struct OutStream* outStream) {
    outStream_writeString(outStream, open);
    for (index_t n=0; n<nElems; ++n) {
        if (n > 0) {
            outStream_writeString(outStream, sep);
        }
        show(elems[n], outStream);
    }
    outStream_writeString(outStream, close);
}

void array_showBindings(count_t nElems, struct Object* elems[], const string_t open, const string_t sep, const string_t close, struct OutStream* outStream) {
    outStream_writeString(outStream, open);
    for (index_t n=0; n<nElems; n+=2) {
        if (n > 0) {
            outStream_writeString(outStream, sep);
        }
        show(elems[n], outStream);
        outStream_writeChar(outStream, '=');
        show(elems[n + 1], outStream);
    }
    outStream_writeString(outStream, close);
}

/* Object functions ******************/

struct Object* array_close_rec(struct Array* array, struct Etor_rec* etor) {
    struct Array* newArray = array_new_noFill(array->nElems);
    array_close_rec_usingElems(array->nElems, array->elems, newArray->elems, etor);
    return (struct Object*)newArray;
}

enum CompareResult array_compare(struct Array* array, struct Array* otherArray) {
    count_t nElems = array->nElems < otherArray->nElems ? array->nElems : otherArray->nElems;
    struct Object** elems = array->elems;
    struct Object** otherElems = otherArray->elems;
    for (count_t n=0; n<nElems; n++) {
        enum CompareResult compareResult = compare(elems[n], otherElems[n]);
        if (compareResult != CompareEqual)
            return compareResult;
    }
    if (array->nElems < otherArray->nElems) {
        return CompareLess;
    }
    if (array->nElems > otherArray->nElems) {
        return CompareGreater;
    }
    return CompareEqual;
}

bool_t array_eval_rec(struct Array* array, struct Etor_rec* etor, struct Object** value) {
    struct Array* newArray = array_new_noFill(array->nElems);
    if (!array_eval_rec_usingElems(array->nElems, array->elems, newArray->elems, etor, value)) {
        return false;
    }
    *value = (struct Object*)newArray;
    return true;
}

bool_t array_match(struct Array* array, struct Array* other, struct Vector* bindings) {
    if (array->nElems != other->nElems) {
        return false;
    }
    return array_match_usingElems(array->nElems, array->elems, other->elems, bindings);
}

void array_show(struct Array* array, struct OutStream* outStream) {
    array_show_usingElems(array->nElems, array->elems, "{", ", ", "}", outStream);
}

/* Private functions *********************************************************/

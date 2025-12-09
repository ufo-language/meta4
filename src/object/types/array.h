#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Array {
    struct Object obj;
    count_t nElems;
    struct Object* elems[];
};

struct Etor_rec;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Array* array_new_elem(count_t nElems, struct Object* elem);
struct Array* array_new_elems(count_t nElems, struct Object* elems[]);
struct Array* array_new_fromArray(count_t nElems, struct Array* oldArray);
struct Array* array_new_noFill(count_t nElems);

/* Public functions **********************************************************/

/* Unique functions ******************/

struct Object* array_get_unsafe(struct Array* array, index_t index);
void array_set_unsafe(struct Array* array, index_t index, struct Object* value);
void array_showElemsWith(count_t nElems, struct Object* elems[], const string_t sep, FILE* stream);

/* Object functions ******************/

bool_t array_close_rec(struct Array* array, struct Etor_rec* etor, struct Object** value);
bool_t array_eval_rec(struct Array* array, struct Etor_rec* etor, struct Object** value);
bool_t array_match(struct Array* array, struct Array* other, struct Vector* bindings);
void array_show(struct Array* array, FILE* stream);

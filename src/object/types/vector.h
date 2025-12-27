#pragma once

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/object.h"
#include "object/types/array.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum {
    DEFAULT_VECTOR_CAPACITY = 8
};

struct Vector {
    struct Object obj;
    count_t nElems;
    count_t nResizes;
    struct Array* elems;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Vector* vector_new(void);
struct Vector* vector_new_withCapacity(count_t capacity);

/* Public functions **********************************************************/

/* Unique functions ******************/

void vector_clear(struct Vector* vector);

index_t vector_top(struct Vector* vector);
void vector_setTop(struct Vector* vector, index_t newTop);

count_t vector_capacity(struct Vector* vector);

void vector_bindPair(struct Vector* vector, struct Object* key, struct Object* value);
bool_t vector_locate(struct Vector* vector, struct Object* key, int_t* index);
bool_t vector_lookup(struct Vector* vector, struct Object* key, struct Object** value);
bool_t vector_get(struct Vector* vector, index_t index, struct Object** elem);
bool_t vector_set(struct Vector* vector, struct Object* indexObj, struct Object* elem, struct Object** error);
void vector_set_raw(struct Vector* vector, index_t index, struct Object* elem);
bool_t vector_pop(struct Vector* vector, struct Object** elem);
void vector_push(struct Vector* vector, struct Object* elem);
bool_t vector_rebind(struct Vector* vector, struct Object* key, struct Object* value);
void vector_showBindings(struct Vector* vector, struct OutStream* outStream);

static inline struct Object* vector_get_unsafe(struct Vector* vector, index_t index) {
    return vector->elems->elems[index];
}

static inline struct Object* vector_pop_unsafe(struct Vector* vector) {
    return vector->elems->elems[--vector->nElems];
}

/* Object functions ******************/

bool_t vector_close_rec(struct Vector* vector, struct Etor_rec* etor, struct Object** value);
count_t vector_count(struct Vector* vector);
bool_t vector_eval_rec(struct Vector* vector, struct Etor_rec* etor, struct Object** value);
void vector_show(struct Vector* vector, struct OutStream* outStream);

#pragma once

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/array.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Vector {
    struct Object obj;
    count_t top;
    // count_t capacity;
    count_t nResizes;
    struct Array* elems;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Vector* vector_new(void);
struct Vector* vector_new_withCapacity(count_t capacity);

/* Public functions **********************************************************/

/* Unique functions ******************/

index_t vector_top(struct Vector* vector);
void vector_setTop(struct Vector* vector, index_t newTop);

count_t vector_capacity(struct Vector* vector);

void vector_bindPair(struct Vector* vector, struct Object* key, struct Object* value);
bool_t vector_lookup(struct Vector* vector, struct Object* key, struct Object** value);
bool_t vector_get(struct Vector* vector, index_t index, struct Object** elem);
bool_t vector_set(struct Vector* vector, index_t index, struct Object* elem);
bool_t vector_pop(struct Vector* vector, struct Object** elem);
void vector_push(struct Vector* vector, struct Object* elem);

/* Object functions ******************/

bool_t vector_close_rec(struct Vector* vector, struct Etor_rec* etor, struct Object** value);
count_t vector_count(struct Vector* vector);
bool_t vector_eval_rec(struct Vector* vector, struct Etor_rec* etor, struct Object** value);
void vector_show(struct Vector* vector, FILE* stream);

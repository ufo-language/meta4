#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/subscript.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct IntArray {
    struct Object obj;
    count_t nElems;
    int_t elems[];
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntArray* intArray_new3(int i1, int i2, int i3);
struct IntArray* intArray_new_elem(count_t nElems, int_t elems);
struct IntArray* intArray_new_elems(count_t nElems, int_t elems[]);
struct IntArray* intArray_new_fromIntArray(count_t nElems, struct IntArray* oldArray);
struct IntArray* intArray_new_noFill(count_t nElems);

/* Public functions **********************************************************/

/* Unique functions ******************/

int_t intArray_get_unsafe(struct IntArray* intArray, index_t index);
enum SubscriptResult intArray_set(struct IntArray* intArray, struct Object* indexObj, struct Object* elemObj);
void intArray_set_unsafe(struct IntArray* intArray, index_t index, int_t elem);

/* Object functions ******************/

void intArray_show(struct IntArray* intArray, struct OutStream* outStream);

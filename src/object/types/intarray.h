#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct IntArray {
    struct Object obj;
    count_t nElems;
    int_t elems[];
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntArray* intArray_new_elem(count_t nElems, int_t elems);
struct IntArray* intArray_new_elems(count_t nElems, int_t elems[]);
struct IntArray* intArray_new_noFill(count_t nElems);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void intArray_show(struct IntArray* intArray, FILE* stream);

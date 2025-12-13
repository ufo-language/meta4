#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct _Symbolic {
    struct Object obj;
    word_t hashCode;
    char name[];
};

struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct _Symbolic* symbolic_new(const string_t name, enum TypeId typeId, struct Vector* internTable);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void symbolic_show(struct _Symbolic* symbolic, FILE* stream);

/* Private functions *********************************************************/

#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Triple {
    struct Object obj;
    struct Object* key;
    struct Object* value;
    struct Triple* next;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Triple* triple_new(struct Object* key, struct Object* value, struct Triple* next);
struct Triple* triple_new_empty(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void triple_show(struct Triple* triple, FILE* stream);

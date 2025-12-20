#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Binding {
    struct Object obj;
    struct Object* key;
    struct Object* value;
    struct Binding* next;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Binding* binding_new(struct Object* key, struct Object* value, struct Binding* next);
struct Binding* binding_new_empty(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void binding_show(struct Binding* triple, struct OutStream* outStream);

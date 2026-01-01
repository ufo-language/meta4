#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Address {
    struct Object obj;
    void* address;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Address* address_new(void* address);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void address_show(struct Address* addr, struct OutStream* outStream);

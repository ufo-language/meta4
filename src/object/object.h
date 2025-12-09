#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object {
    enum TypeId typeId;
    count_t nWords;
};

struct Etor_rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Object* object_new(enum TypeId typeId, count_t nWords);

/* Public functions **********************************************************/

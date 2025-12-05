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

struct Evaluator;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Object* object_new(enum TypeId typeId, count_t nWords);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

#if 0
typedef void (*EvalFunction)(struct Object* obj, struct Evaluator* etor);

struct EvalFunction_handler {
    enum TypeID typeId;
    EvalFunction function;
};

typedef void (*ShowFunction)(struct Object* obj, FILE* stream);

struct ShowFunction_handler {
    enum TypeID typeId;
    ShowFunction function;
};
#endif

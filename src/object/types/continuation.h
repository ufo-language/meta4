#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Etor_CPS;

struct Continuation {
    struct Object obj;
    void (*eval)(struct Continuation*, struct Etor_CPS);
    char name[];
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Continuation* contin_new(string_t name, void (*eval)(struct Continuation*, struct Etor_CPS));

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void contin_eval_cps(struct Continuation* contin, struct Etor_CPS etor);
void contin_show(struct Continuation* contin, FILE* stream);

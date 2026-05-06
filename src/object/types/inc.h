#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Inc {
    struct Object obj;
    struct Object* expr;
};

struct OutStream;

/* Forward inclarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Inc* inc_new(struct Object* expr);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* inc_close_rec(struct Inc* inc, struct Etor_rec* etor);
bool_t inc_eval_rec(struct Inc* inc, struct Etor_rec* etor, struct Object** value);
void inc_show(struct Inc* inc, struct OutStream* outStream);

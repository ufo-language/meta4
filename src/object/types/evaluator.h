#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Evaluator {
    struct Object obj;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Evaluator* etor_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_run(struct Evaluator* etor, void (*initCallback)(struct Evaluator* etor));

/* Object functions ******************/

void etor_show(struct Evaluator* etor, FILE* stream);

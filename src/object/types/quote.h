#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Quote {
    struct Object obj;
    struct Object* expr;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Quote* quote_new(struct Object* expr);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t quote_eval_rec(struct Quote* quote, struct Etor_rec* etor, struct Object **value);
void quote_show(struct Quote* quote, struct OutStream* outStream);

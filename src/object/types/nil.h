#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Nil {
    struct Object obj;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Nil* nil_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t nil_eval_rec(struct Nil* nil, struct Etor_rec* etor, struct Object** value);
bool_t nil_hash(struct Nil* nil, word_t* hashCode);
void nil_show(struct Nil* nil, struct OutStream* outStream);

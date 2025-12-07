#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

#if 0
struct Identifier {
    struct Object obj;
    word_t hashCode;
    char name[];
};
#endif

struct Etor_Rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* identifier_new(const string_t name);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t identifier_eval_rec(struct Symbolic* ident, struct Etor_Rec* etor, struct Object** value);
void identifier_show(struct Symbolic* ident, FILE* stream);

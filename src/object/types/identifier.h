#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Identifier {
    #include "object/types/symbolic_fields.h"
};

struct Etor_rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Identifier* identifier_new(const string_t name);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* identifier_close_rec(struct Identifier* ident, struct Etor_rec* etor);
bool_t identifier_eval_rec(struct Identifier* ident, struct Etor_rec* etor, struct Object** value);
void identifier_show(struct Identifier* ident, FILE* stream);

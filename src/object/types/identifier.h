#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/compare.h"
#include "object/object.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Identifier {
    #include "object/types/symbolic_fields.h"
};

struct Etor_rec;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Identifier* identifier_new(const string_t name);

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t identifier_assign(struct Identifier* ident, struct Object* value, struct Etor_rec* etor);

/* Object functions ******************/

struct Object* identifier_close_rec(struct Identifier* ident, struct Etor_rec* etor);
enum CompareResult identifier_compare(struct Identifier* ident, struct Identifier* otherIdent);
bool_t identifier_eval_rec(struct Identifier* ident, struct Etor_rec* etor, struct Object** value);

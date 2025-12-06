#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Identifier {
    struct Object obj;
    string_t name;
    word_t hashCode;
};

struct Evaluator;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Identifier* identifier_new(const string_t name);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* bool_t identifier_equal(struct Identifier* ident, struct Identifier* otherIdent); */
bool_t identifier_eval_recursive(struct Identifier* ident, struct Evaluator* etor, struct Object** value);
void identifier_show(struct Identifier* ident, FILE* stream);

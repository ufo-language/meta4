#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct While {
    struct Object obj;
    struct Object* cond;
    struct Object* body;
};

struct Etor_rec;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct While* while_new(struct Object* cond, struct Object* body);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* while_close_rec(struct While* while_, struct Etor_rec* etor);
bool_t while_eval_rec(struct While* while_, struct Etor_rec* etor, struct Object** value);
void while_show(struct While* while_, struct OutStream* outStream);

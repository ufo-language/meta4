#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Subscript {
    struct Object obj;
    struct Object* base;
    struct Object* index;
};

struct Etor_rec;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Subscript* subscript_new(struct Object* base, struct Object* index);

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t subscript_assign(struct Subscript* subs, struct Object* value, struct Object** error);

/* Object functions ******************/

struct Object* subscript_close_rec(struct Subscript* subscript, struct Etor_rec* etor);
bool_t subscript_eval_rec(struct Subscript* subscript, struct Etor_rec* etor, struct Object** value);
void subscript_show(struct Subscript* subscript, struct OutStream* outStream);

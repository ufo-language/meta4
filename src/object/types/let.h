#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Let {
    struct Object obj;
    struct Object* lhs;
    struct Object* rhs;
};

struct Etor_rec;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Let* let_new(struct Object* lhs, struct Object* rhs);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

struct Object* let_close_rec(struct Let* let, struct Etor_rec* etor);
bool_t let_eval_rec(struct Let* let, struct Etor_rec* etor, struct Object** value);
void let_show(struct Let* let, struct OutStream* outStream);

#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Term {
    struct Object obj;
    struct Symbol* name;
    struct Object* attrib;
    count_t nArgs;
    struct Object* args[];
};

struct Etor_rec;
struct Symbol;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

struct Term* term_new(struct Symbol* name, struct Object* attrib, count_t nArgs, struct Object* args[]);

/* Unique functions ******************/

/* Object functions ******************/

bool_t term_close(struct Term* term, struct Etor_rec* etor, struct Object** value);
bool_t term_equal(struct Term* term, struct Term* other);
bool_t term_eval_rec(struct Term* term, struct Etor_rec* etor, struct Object** value);
void term_freeVars(struct Object* obj, struct Vector* freeVars);
bool_t term_match(struct Object* obj, struct Object* other, struct Vector* bindings);
void term_show(struct Term* term, FILE* stream);

#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Etor_rec {
    struct Object obj;
    struct Vector* env;
};

struct Identifier;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Etor_rec* etor_rec_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void    etor_rec_bind      (struct Etor_rec* etor, struct Identifier* name, struct Object* value);
void    etor_rec_envRestore(struct Etor_rec* etor, index_t savedEnv);
index_t etor_rec_envSave   (struct Etor_rec* etor);
bool_t  etor_rec_lookup    (struct Etor_rec* etor, struct Identifier* name, struct Object** value);
void    etor_rec_run       (struct Etor_rec* etor);

/* Object functions ******************/

void etor_rec_show(struct Etor_rec* etor, FILE* stream);

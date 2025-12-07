#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum EvaluationType {
    Etor_Closing,
    Etor_Evaluating
};

struct Etor_Rec {
    struct Object obj;
    enum EvaluationType evaluationType;
    struct Vector* env;
};

struct Symbolic;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Etor_Rec* etor_rec_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_rec_bind(struct Etor_Rec* etor, struct Symbolic* name, struct Object* value);
bool_t etor_rec_lookup(struct Etor_Rec* etor, struct Symbolic* name, struct Object** value);
void etor_rec_run(struct Etor_Rec* etor);

/* Object functions ******************/

void etor_rec_show(struct Etor_Rec* etor, FILE* stream);

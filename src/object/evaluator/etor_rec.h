#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum OperationType {
    Etor_Closing,
    Etor_Evaluating
};

struct Evaluator {
    struct Object obj;
    enum OperationType operationType;
    struct Vector* env;
};

struct Symbolic;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Evaluator* etor_rec_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_rec_bind(struct Evaluator* etor, struct Symbolic* name, struct Object* value);
bool_t etor_rec_lookup(struct Evaluator* etor, struct Symbolic* name, struct Object** value);
void etor_rec_run(struct Evaluator* etor);

/* Object functions ******************/

void etor_rec_show(struct Evaluator* etor, FILE* stream);

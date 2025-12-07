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

struct Vector;

struct Evaluator {
    struct Object obj;
    enum OperationType operationType;
    struct Vector* vStack;
    struct Vector* eStack;
    struct Vector* env;
    struct IntVector* iStack;
};

struct Symbolic;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Evaluator* etor_rec_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_cps_vPush(struct Etor_CPS* etor, struct Object* value);
struct Object* etor_cps_vPop(struct Etor_CPS* etor;

void etor_cps_bind(struct Evaluator* etor, struct Symbolic* name, struct Object* value);
bool_t etor_cps_lookup(struct Evaluator* etor, struct Symbolic* name, struct Object** value);
void etor_cps_run(struct Evaluator* etor);

/* Object functions ******************/

void etor_cps_show(struct Evaluator* etor, FILE* stream);

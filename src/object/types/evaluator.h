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
struct IntVector;

struct Evaluator {
    struct Object obj;
    enum OperationType operationType;
    struct Vector* vStack;
    struct Vector* eStack;
    struct Vector* env;
    struct IntVector* iStack;
};

struct Identifier;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Evaluator* evaluator_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void evaluator_bind(struct Evaluator* etor, struct Identifier* name, struct Object* value);
bool_t evaluator_lookup(struct Evaluator* etor, struct Identifier* name, struct Object** value);
void evaluator_run(struct Evaluator* etor);

/* Object functions ******************/

void evaluator_show(struct Evaluator* etor, FILE* stream);

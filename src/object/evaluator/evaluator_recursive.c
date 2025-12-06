#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/evaluator/evaluator_recursive.h"
#include "object/types/intvector.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Evaluator* evaluator_new(void) {
    struct Evaluator* etor = (struct Evaluator*)object_new(OT_Evaluator, NWORDS(*etor));
    /* etor->vStack = vector_new(); */
    /* etor->eStack = vector_new(); */
    etor->env = vector_new();
    /* etor->iStack = intVector_new(); */
    return etor;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void evaluator_bind(struct Evaluator* etor, struct Identifier* name, struct Object* value) {
    vector_push(etor->env, (struct Object*)name);
    vector_push(etor->env, value);
}

bool_t evaluator_lookup(struct Evaluator* etor, struct Identifier* name, struct Object** value) {
    return vector_lookup(etor->env, (struct Object*)name, value);
}

void evaluator_run(struct Evaluator* etor) {
}

/* Object functions ******************/

void evaluator_show(struct Evaluator* etor, FILE* stream) {
}

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/intvector.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Etor_Rec* etor_rec_new(void) {
    struct Etor_Rec* etor = (struct Etor_Rec*)object_new(OT_Etor_Rec, NWORDS(*etor));
    etor->env = vector_new();
    return etor;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_rec_bind(struct Etor_Rec* etor, struct Identifier* name, struct Object* value) {
    vector_push(etor->env, (struct Object*)name);
    vector_push(etor->env, value);
}

bool_t etor_rec_lookup(struct Etor_Rec* etor, struct Identifier* name, struct Object** value) {
    return vector_lookup(etor->env, (struct Object*)name, value);
}

void etor_rec_run(struct Etor_Rec* etor) {
    /* TODO */
}

/* Object functions ******************/

void etor_rec_show(struct Etor_Rec* etor, FILE* stream) {
    /* TODO */
}

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/evaluator/etor_cps.h"
#include "object/types/intvector.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Etor_CPS* etor_cps_new(void) {
    struct Etor_CPS* etor = (struct Etor_CPS*)object_new(OT_Etor_Rec, NWORDS(*etor));
    etor->vStack = vector_new();
    etor->eStack = vector_new();
    etor->env = vector_new();
    etor->iStack = intVector_new();
    return etor;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_cps_ePush(struct Etor_CPS* etor, struct Object* value);
struct Object* etor_cps_ePop(struct Etor_CPS* etor);

void etor_cps_vPush(struct Etor_CPS* etor, struct Object* value);
struct Object* etor_cps_vPop(struct Etor_CPS* etor);

void etor_cps_iPush(struct Etor_CPS* etor, int_t value);
struct int_t etor_cps_iPop(struct Etor_CPS* etor);

void etor_cps_bind(struct Etor_CPS* etor, struct Symbolic* name, struct Object* value) {
    vector_push(etor->env, (struct Object*)name);
    vector_push(etor->env, value);
}

bool_t etor_cps_lookup(struct Etor_CPS* etor, struct Symbolic* name, struct Object** value) {
    return vector_lookup(etor->env, (struct Object*)name, value);
}

void etor_cps_run(struct Etor_CPS* etor) {
    /* TODO */
    (void)etor;
}

/* Object functions ******************/

void etor_cps_show(struct Etor_CPS* etor, FILE* stream) {
    /* TODO */
    (void)etor;
    (void)stream;
}

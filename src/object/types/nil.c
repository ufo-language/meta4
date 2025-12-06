#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/nil.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Nil* nil_new(void) {
    return (struct Nil*)object_new(OT_Nil, NWORDS(struct Nil));
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t nil_eval_recursive(struct Nil* nil, struct Evaluator* etor, struct Object** value) {
    *value = (struct Object*)nil;
    return true;
}

void nil_show(struct Nil* nil, FILE* stream) {
    fputs("nil", stream);
}

/* Private functions *********************************************************/

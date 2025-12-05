#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/eval.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/boolean.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Boolean* boolean_new(bool_t b) {
    struct Boolean* boolean = (struct Boolean*)object_new(OT_Boolean, NWORDS(*boolean));
    boolean->b = b;
    return boolean;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t boolean_eval(struct Boolean* boolean, struct Evaluator* etor, struct Object** value) {
    *value = (struct Object*)boolean;
    return true;
}

void boolean_show(struct Boolean* boolean, FILE* stream) {
    fputs(boolean->b ? "true" : "false", stream);
}

/* Private functions *********************************************************/

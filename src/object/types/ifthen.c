#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/boolvalue.h"
#include "object/functions/eval.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/ifthen.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IfThen* ifThen_new(struct Object* cond, struct Object* conseq, struct Object* alt) {
    struct IfThen* ifThen = (struct IfThen*)object_new(OT_IfThen, NWORDS(*ifThen));
    ifThen->cond = cond;
    ifThen->conseq = conseq;
    ifThen->alt = alt;
    return ifThen;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

bool_t ifThen_eval(struct IfThen* ifThen, struct Evaluator* etor, struct Object** value) {
    if (!eval(ifThen->cond, etor, value)) {
        return false;
    }
    bool_t b = boolValue(*value);
    return eval(b ? ifThen->conseq : ifThen->alt, etor, value);
}

void ifThen_show(struct IfThen* ifThen, FILE* stream) {
    fputs("if ", stream);
    show(ifThen->cond, stream);
    fputs(" then ", stream);
    show(ifThen->conseq, stream);
    fputs(" else ", stream);
    show(ifThen->alt, stream);
    fputs(" end", stream);
}

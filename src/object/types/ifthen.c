#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/boolvalue.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
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

bool_t ifThen_close_rec(struct IfThen* ifThen, struct Etor_rec* etor, struct Object** value) {
    struct Object* closedCond;
    if (!close_rec(ifThen->cond, etor, &closedCond)) {
        return false;
    }
    if (closedCond->typeId < OT_ConstantLimit) {
        bool_t b = boolValue(*value);
        return close_rec(b ? ifThen->conseq : ifThen->alt, etor, value);
    }
    struct Object* closedConseq;
    if (!close_rec(ifThen->conseq, etor, &closedConseq)) {
        return false;
    }
    struct Object* closedAlt;
    if (!close_rec(ifThen->alt, etor, &closedAlt)) {
        return false;
    }
    *value = (struct Object*)ifThen_new(closedCond, closedConseq, closedAlt);
    return true;
}

bool_t ifThen_eval_rec(struct IfThen* ifThen, struct Etor_rec* etor, struct Object** value) {
    if (!eval_rec(ifThen->cond, etor, value)) {
        return false;
    }
    bool_t b = boolValue(*value);
    return eval_rec(b ? ifThen->conseq : ifThen->alt, etor, value);
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

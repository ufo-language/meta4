#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/boolvalue.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/ifthen.h"
#include "object/types/outstream.h"

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

struct Object* ifThen_close_rec(struct IfThen* ifThen, struct Etor_rec* etor) {
    struct Object* closedCond = close_rec(ifThen->cond, etor);
    struct Object* closedConseq = close_rec(ifThen->conseq, etor);
    struct Object* closedAlt = close_rec(ifThen->alt, etor);
    return (struct Object*)ifThen_new(closedCond, closedConseq, closedAlt);
}

bool_t ifThen_eval_rec(struct IfThen* ifThen, struct Etor_rec* etor, struct Object** value) {
    if (!eval_rec(ifThen->cond, etor, value)) {
        return false;
    }
    bool_t b = boolValue(*value);
    return eval_rec(b ? ifThen->conseq : ifThen->alt, etor, value);
}

void ifThen_show(struct IfThen* ifThen, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'S', "if ",
        'O', ifThen->cond,
        'S', " then ",
        'O', ifThen->conseq,
        'S', " else ",
        'O', ifThen->alt,
        0);
}

#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/typeids.h"
#include "object/types/inc.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward inclarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Inc* inc_new(struct Object* expr) {
    struct Inc* inc = (struct Inc*)object_new(OT_Inc, NWORDS(*inc));
    inc->expr = expr;
    return inc;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t inc_eval_rec(struct Inc* inc, struct Etor_rec* etor, struct Object** value) {
    struct Object* exprValue;
    if (!eval_rec(inc->expr, etor, &exprValue)) {
        return false;
    }
    switch (exprValue->typeId) {
        case OT_Integer:
            *value = (struct Object*)integer_new(((struct Integer*)exprValue)->i + 1);
            return true;
        case OT_IntVar:
            ++((struct IntVar*)exprValue)->i;
            *value = exprValue;
            return true;
        default:
            fputs("ERROR: inc_eval unable to inc object", stderr);
            show(exprValue, stderr);
            fputc('\n', stderr);
            return false;
    }
}

void inc_show(struct Inc* inc, FILE* stream) {
    fputs("Inc(", stream);
    show(inc->expr, stream);
    fputc(')', stream);
}

/* Private functions *********************************************************/

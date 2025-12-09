#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/typeids.h"
#include "object/types/dec.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Dec* dec_new(struct Object* expr) {
    struct Dec* dec = (struct Dec*)object_new(OT_Dec, NWORDS(*dec));
    dec->expr = expr;
    return dec;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t dec_eval_rec(struct Dec* dec, struct Etor_rec* etor, struct Object** value) {
    struct Object* exprValue;
    if (!eval_rec(dec->expr, etor, &exprValue)) {
        return false;
    }
    switch (exprValue->typeId) {
        case OT_Integer:
            *value = (struct Object*)integer_new(((struct Integer*)exprValue)->i - 1);
            return true;
        case OT_IntVar:
            --((struct IntVar*)exprValue)->i;
            *value = exprValue;
            return true;
        default:
            fputs("ERROR: dec_eval unable to dec object", stderr);
            show(exprValue, stderr);
            fputc('\n', stderr);
            return false;
    }
}

void dec_show(struct Dec* dec, FILE* stream) {
    fputs("Dec{", stream);
    show(dec->expr, stream);
    fputc('}', stream);
}

/* Private functions *********************************************************/

#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/sequence.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Sequence* sequence_new(count_t nExprs, struct Object* exprs[]) {
    struct Sequence* seq = (struct Sequence*)object_new(OT_Sequence, NWORDS(*seq) + nExprs);
    seq->nExprs = nExprs;
    memcpy(seq->exprs, exprs, sizeof(struct Object*) * nExprs);
    return seq;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t sequence_close_rec(struct Sequence* seq, struct Etor_rec* etor, struct Object** value) {
    struct Vector* values = vector_new();
    struct Object* value1;
    for (index_t n=0; n<seq->nExprs; ++n) {
        if (!close_rec(seq->exprs[n], etor, &value1)) {
            return false;
        }
        if (value1->typeId > OT_ConstantLimit) {
            vector_push(values, value1);
        }
    }
    switch (values->top) {
        case 0:
            *value = (struct Object*)g_nil;
            break;
        case 1:
            *value = values->elems->elems[0];
            break;
        default:
            *value = (struct Object*)sequence_new(values->top, values->elems->elems);
            break;
    }
    return true;
}

bool_t sequence_eval_rec(struct Sequence* seq, struct Etor_rec* etor, struct Object** value) {
    *value = (struct Object*)g_nil;
    for (index_t n=0; n<seq->nExprs; ++n) {
        if (!eval_rec(seq->exprs[n], etor, value)) {
            return false;
        }
    }
    return true;
}

void sequence_show(struct Sequence* seq, FILE* stream) {
    fputc('(', stream);
    array_showElemsWith(seq->nExprs, seq->exprs, "; ", stream);
    fputc(')', stream);
}

/* Private functions *********************************************************/

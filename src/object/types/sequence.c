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

struct Object* sequence_close_rec(struct Sequence* seq, struct Etor_rec* etor) {
    struct Vector* values = vector_new();
    for (index_t n=0; n<seq->nExprs; ++n) {
        struct Object* value = close_rec(seq->exprs[n], etor);
        if (value->typeId > OT_ConstantLimit) {
            vector_push(values, value);
        }
    }
    switch (values->top) {
        case 0:
            return (struct Object*)g_nil;
        case 1:
            return values->elems->elems[0];
        default:
            return (struct Object*)sequence_new(values->top, values->elems->elems);
    }
}

bool_t sequence_eval_rec(struct Sequence* seq, struct Etor_rec* etor, struct Object** value) {
    index_t savedEnv = etor_rec_envSave(etor);
    *value = (struct Object*)g_nil;
    for (index_t n=0; n<seq->nExprs; ++n) {
        if (!eval_rec(seq->exprs[n], etor, value)) {
            etor_rec_envRestore(etor, savedEnv);
            return false;
        }
    }
    etor_rec_envRestore(etor, savedEnv);
    return true;
}

void sequence_show(struct Sequence* seq, FILE* stream) {
    fputc('(', stream);
    array_showElems(seq->nExprs, seq->exprs, "; ", stream);
    fputc(')', stream);
}

/* Private functions *********************************************************/

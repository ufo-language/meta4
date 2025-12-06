#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/functions/eval.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/evaluator.h"
#include "object/types/sequence.h"

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

bool_t sequence_eval(struct Sequence* seq, struct Evaluator* etor, struct Object** value) {
    *value = (struct Object*)g_nil;
    for (index_t n=0; n<seq->nExprs; ++n) {
        if (!eval(seq->exprs[n], etor, value)) {
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

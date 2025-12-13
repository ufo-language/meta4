#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/boolvalue.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/while.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct While* while_new(struct Object* cond, struct Object* body) {
    struct While* while_ = (struct While*)object_new(OT_While, NWORDS(*while_));
    while_->cond = cond;
    while_->body = body;
    return while_;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* while_close_rec(struct While* while_, struct Etor_rec* etor) {
    struct Object* closedCond = close_rec(while_->cond, etor);
    struct Object* closedBody = close_rec(while_->body, etor);
    struct While* closedWhile = while_new(closedCond, closedBody);
    return (struct Object*)closedWhile;
}

bool_t while_eval_rec(struct While* while_, struct Etor_rec* etor, struct Object** value) {
    struct Object* cond = while_->cond;
    struct Object* body = while_->body;
    struct Object* condValue;
    struct Object* bodyValue = (struct Object*)g_nil;
    for (;;) {
        if (!eval_rec(cond, etor, &condValue)) {
            return false;
        }
        if (!boolValue(condValue)) {
            break;
        }
        if (!eval_rec(body, etor, &bodyValue)) {
            return false;
        }
    }
    *value = bodyValue;
    return true;
}

void while_show(struct While* while_, FILE* stream) {
    fputs("while ", stream);
    show(while_->cond, stream);
    fputc(' ', stream);
    show(while_->body, stream);
}

/* Private functions *********************************************************/

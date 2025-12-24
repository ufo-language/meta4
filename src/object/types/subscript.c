#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/outstream.h"
#include "object/types/subscript.h"
#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Subscript* subscript_new(struct Object* base, struct Object* index) {
    struct Subscript* subs = (struct Subscript*)object_new(OT_Subscript, NWORDS(struct Subscript));
    subs->base = base;
    subs->index = index;
    return subs;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* subscript_close_rec(struct Subscript* subs, struct Etor_rec* etor) {
    struct Object* closedBase = close_rec(subs->base, etor);
    struct Object* closedIndex = close_rec(subs->index, etor);
    return (struct Object*)subscript_new(closedBase, closedIndex);
}

bool_t subscript_eval_rec(struct Subscript* subs, struct Etor_rec* etor, struct Object** value) {
    struct Object* base;
    if (!eval_rec(subs->base, etor, &base)) {
        return false;
    }
    struct Object* index;
    if (!eval_rec(subs->index, etor, &index)) {
        return false;
    }
    switch (base->typeId) {
        case OT_Array:
            return array_get((struct Array*)base, index, value);
        default:
            *value = (struct Object*)errorTerm1("SubscriptError", "Base object is not subscriptable", base);
            return false;
    }
}

void subscript_show(struct Subscript* subs, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'O', subs->base,
        'C', '[',
        'O', subs->index,
        'C', ']',
        0);
}

/* Private functions *********************************************************/

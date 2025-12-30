#include <assert.h>

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/hashtable.h"
#include "object/types/intarray.h"
#include "object/types/integer.h"
#include "object/types/intvector.h"
#include "object/types/outstream.h"
#include "object/types/subscript.h"
#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

struct Term* _errorTerm(enum SubscriptResult subscriptResult, struct Object* base, struct Object* index);

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

enum SubscriptResult subscript_assign(struct Object* base, struct Object* index, struct Object* value) {
    switch (base->typeId) {
        case OT_Array:
            return array_set((struct Array*)base, index, value);
        case OT_HashTable:
            return hashTable_put((struct HashTable*)base, index, value);
        case OT_IntArray:
            return intArray_set((struct IntArray*)base, index, value);
        case OT_IntVector:
            return intVector_set((struct IntVector*)base, index, value);
        default:
            return SubscriptResult_ObjectNotSubscriptable;
    }
}

bool_t subscript_evalParts(struct Object* baseObj,
                           struct Object* indexObj,
                           struct Etor_rec* etor,
                           struct Object** base,
                           struct Object** index,
                           struct Object** error) {
    struct Object* tempValue;
    if (!eval_rec(baseObj, etor, &tempValue)) {
        *error = tempValue;
        return false;
    }
    *base = tempValue;
    if (!eval_rec(indexObj, etor, &tempValue)) {
        *error = tempValue;
        return false;
    }
    *index = tempValue;
    return true;
}

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
    enum SubscriptResult subscriptResult;
    switch (base->typeId) {
        case OT_Array:
            subscriptResult = array_get((struct Array*)base, index, value);
            switch (subscriptResult) {
                case SubscriptResult_OK:
                    return true;
                default:
                    *value = (struct Object*)_errorTerm(subscriptResult, base, index);
                    return false;;
            }
            break;
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

struct Term* _errorTerm(enum SubscriptResult subscriptResult, struct Object* base, struct Object* index) {
    switch (subscriptResult) {
        case SubscriptResult_IndexOutOfBounds:
            return errorTerm1("SubscriptError", "Index out of bounds", index);
        case SubscriptResult_IndexType:
            return errorTerm_objAndType("SubscriptError", "Index type error", index);
        case SubscriptResult_KeyNotFound:
            return errorTerm_objAndType("SubscriptError", "Key not found", index);
        case SubscriptResult_UnhashableKey:
            return errorTerm_objAndType("SubscriptError", "Unhashable key", index);
        case SubscriptResult_ObjectNotSubscriptable:
            return errorTerm_objAndType("SubscriptError", "Object is not subscriptable", base);
        default:
            return errorTerm1("SubscriptError", "Unhandled SubscriptResult enum value", (struct Object*)integer_new(subscriptResult));
    }
}

#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/outstream.h"
#include "object/types/pair.h"
#include "object/types/queue.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Queue* queue_new(void) {
    struct Queue* q = (struct Queue*)object_new(OT_Queue, NWORDS(struct Queue));
    q->first = g_emptyPair;
    q->last = g_emptyPair;
    q->nElems = 0;
    return q;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void queue_enq(struct Queue* q, struct Object* elem) {
    struct Pair* pair = pair_new(elem, (struct Object*)g_emptyPair);
    if (q->nElems == 0) {
        q->first = q->last = pair;
    }
    else {
        q->last->rest = (struct Object*)pair;
        q->last = pair;
    }
    ++q->nElems;
}

bool_t queue_deq(struct Queue* q, struct Object** elem) {
    if (q->nElems == 0) {
        return false;
    }
    *elem = q->first->first;
    q->first = (struct Pair*)q->first->rest;
    if (--q->nElems == 0) {
        q->last = g_emptyPair;
    }
    return true;
}

/* Object functions ******************/

count_t queue_count(struct Queue* q) {
    return q->nElems;
}

void queue_show(struct Queue* q, struct OutStream* outStream) {
    pair_showWith(q->first, "~[", "]", outStream);
}

/* Private functions *********************************************************/

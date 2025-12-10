#include <stdio.h>

#include "_typedefs.h"

#include "object/globals.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/match.h"
#include "object/functions/show.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/pair.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Pair* pair_new(struct Object* first, struct Object* rest) {
    struct Pair* pair = (struct Pair*)object_new(OT_Pair, NWORDS(*pair));
    pair->first = first;
    pair->rest = rest;
    return pair;
}

struct Pair* pair_new_empty(void) {
    struct Pair* pair = (struct Pair*)object_new(OT_Pair, NWORDS(*pair));
    pair->first = (struct Object*)g_nil;
    pair->rest = (struct Object*)pair;
    return pair;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

count_t pair_count(struct Pair* pair) {
    count_t count = 0;
    while (pair != g_emptyPair) {
        ++count;
        if (pair->rest->typeId == OT_Pair) {
            pair = (struct Pair*)pair->rest;
        }
        else {
            ++count;
            break;
        }
    }
    return count;
}

bool_t pair_close_rec(struct Pair* pair, struct Etor_rec* etor, struct Object** value) {
    if (pair == g_emptyPair) {
        *value = (struct Object*)pair;
        return true;
    }
    struct Object* newFirst;
    if (!close_rec(pair->first, etor, &newFirst)) {
        return false;
    }
    struct Object* newRest;
    if (!close_rec(pair->rest, etor, &newRest)) {
        return false;
    }
    *value = (struct Object*)pair_new(newFirst, newRest);
    return true;
}

bool_t pair_eval_rec(struct Pair* pair, struct Etor_rec* etor, struct Object** value) {
    if (pair == g_emptyPair) {
        *value = (struct Object*)pair;
        return true;
    }
    struct Object* newFirst;
    if (!eval_rec(pair->first, etor, &newFirst)) {
        return false;
    }
    struct Object* newRest;
    if (!eval_rec(pair->rest, etor, &newRest)) {
        return false;
    }
    *value = (struct Object*)pair_new(newFirst, newRest);
    return true;
}

bool_t pair_match(struct Pair* pair, struct Pair* other, struct Vector* bindings) {
    if (pair == g_emptyPair || other == g_emptyPair) {
        return false;
    }
    index_t savedTop = vector_top(bindings);
    if (!match(pair->first, other->first, bindings)) {
        vector_setTop(bindings, savedTop);
        return false;
    }
    return match(pair->rest, other->rest, bindings);
}

void pair_show(struct Pair* pair, FILE* stream) {
    fputc('[', stream);
    for (bool_t firstIter=true; pair!=g_emptyPair; firstIter=false) {
        if (!firstIter) {
            fputs(", ", stream);
        }
        show(pair->first, stream);
        if (pair->rest->typeId == OT_Pair) {
            pair = (struct Pair*)pair->rest;
        }
        else {
            fputs(" | ", stream);
            show(pair->rest, stream);
            break;
        }
    }
    fputc(']', stream);
}

/* Private functions *********************************************************/

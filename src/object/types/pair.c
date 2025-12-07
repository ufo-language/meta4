#include <stdio.h>

#include "_typedefs.h"

#include "object/globals.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/pair.h"

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

bool_t pair_eval_rec(struct Pair* pair, struct Etor_Rec* etor, struct Object** value) {
    struct Object* newFirst;
    eval_rec(pair->first, etor, &newFirst);
    struct Object* newRest;
    eval_rec(pair->rest, etor, &newRest);
    *value = (struct Object*)pair_new(newFirst, newRest);
    return true;
}

void pair_show(struct Pair* pair, FILE* stream) {
    bool_t firstIter = true;
    fputc('[', stream);
    while (pair != g_emptyPair) {
        if (firstIter) {
            firstIter = false;
        }
        else {
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

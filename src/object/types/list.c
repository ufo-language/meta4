#include <stdio.h>

#include "_typedefs.h"

#include "object/globals.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/list.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct List* list_new(struct Object* first, struct Object* rest) {
    struct List* list = (struct List*)object_new(OT_List, NWORDS(*list));
    list->first = first;
    list->rest = rest;
    return list;
}

struct List* list_new_empty(void) {
    struct List* list = (struct List*)object_new(OT_List, NWORDS(*list));
    list->first = (struct Object*)g_nil;
    list->rest = (struct Object*)list;
    return list;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

count_t list_count(struct List* list) {
    count_t count = 0;
    while (list != g_emptyList) {
        ++count;
        if (list->rest->typeId == OT_List) {
            list = (struct List*)list->rest;
        }
        else {
            ++count;
            break;
        }
    }
    return count;
}

bool_t list_eval(struct List* list, struct Etor_Rec* etor, struct Object** value) {
    struct Object* newFirst;
    eval_rec(list->first, etor, &newFirst);
    struct Object* newRest;
    eval_rec(list->rest, etor, &newRest);
    *value = (struct Object*)list_new(newFirst, newRest);
    return true;
}

void list_show(struct List* list, FILE* stream) {
    bool_t firstIter = true;
    fputc('[', stream);
    while (list != g_emptyList) {
        if (firstIter) {
            firstIter = false;
        }
        else {
            fputs(", ", stream);
        }
        show(list->first, stream);
        if (list->rest->typeId == OT_List) {
            list = (struct List*)list->rest;
        }
        else {
            fputs(" | ", stream);
            show(list->rest, stream);
            break;
        }
    }
    fputc(']', stream);
}

/* Private functions *********************************************************/

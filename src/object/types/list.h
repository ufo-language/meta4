#include <stdio.h>

#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct List {
    struct Object obj;
    struct Object* first;
    struct Object* rest;
};

struct Etor_Rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct List* list_new(struct Object* first, struct Object* rest);
struct List* list_new_empty(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

count_t list_count(struct List* list);
bool_t list_eval(struct List* list, struct Etor_Rec* etor, struct Object** value);
void list_show(struct List* list, FILE* stream);

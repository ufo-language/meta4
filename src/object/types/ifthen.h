#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct IfThen {
    struct Object obj;
    struct Object* cond;
    struct Object* conseq;
    struct Object* alt;
};

struct Etor_CPS;
struct Etor_Rec;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IfThen* ifThen_new(struct Object* cond, struct Object* conseq, struct Object* alt);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void ifThen_eval_cps(struct IfThen* ifThen, struct Etor_CPS* etor);
bool_t ifThen_eval_rec(struct IfThen* ifThen, struct Etor_Rec* etor, struct Object** value);
void ifThen_show(struct IfThen* ifThen, FILE* stream);

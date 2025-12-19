#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum EvaluationType {
    Etor_Closing,
    Etor_Evaluating
};

struct Vector;

struct Etor_CPS {
    struct Object obj;
    enum EvaluationType operationType;
    struct Vector* vStack;
    struct Vector* eStack;
    struct Vector* env;
    struct IntVector* iStack;
};

struct Symbolic;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Etor_CPS* etor_cps_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void etor_cps_ePush(struct Etor_CPS* etor, struct Object* value);
struct Object* etor_cps_ePop(struct Etor_CPS* etor);

void etor_cps_vPush(struct Etor_CPS* etor, struct Object* value);
struct Object* etor_cps_vPop(struct Etor_CPS* etor);

void etor_cps_iPush(struct Etor_CPS* etor, int_t value);
struct int_t etor_cps_iPop(struct Etor_CPS* etor);

void etor_cps_bind(struct Etor_CPS* etor, struct Symbolic* name, struct Object* value);
bool_t etor_cps_lookup(struct Etor_CPS* etor, struct Symbolic* name, struct Object** value);
void etor_cps_run(struct Etor_CPS* etor);

/* Object functions ******************/

void etor_cps_show(struct Etor_CPS* etor, struct OutStream* outStream);

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

struct Evaluator;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IfThen* ifThen_new(struct Object* cond, struct Object* conseq, struct Object* alt);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t ifThen_eval(struct IfThen* ifThen, struct Evaluator* etor, struct Object** value);
void ifThen_show(struct IfThen* ifThen, FILE* stream);

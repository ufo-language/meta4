#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Boolean {
    struct Object obj;
    bool_t b;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Boolean* boolean_new(bool_t b);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t boolean_eval(struct Boolean* boolean, struct Evaluator* etor, struct Object** value);
void boolean_show(struct Boolean* boolean, FILE* stream);

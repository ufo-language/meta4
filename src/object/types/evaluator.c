#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/evaluator.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Evaluator* evaluator_new(void) {
    struct Evaluator* etor = (struct Evaluator*)object_new(OT_Evaluator, NWORDS(*etor));
    return etor;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void evaluator_run(struct Evaluator* etor, void (*initCallback)(struct Evaluator* etor)) {
    initCallback(etor);
}

/* Object functions ******************/

void evaluator_show(struct Evaluator* etor, FILE* stream) {
}

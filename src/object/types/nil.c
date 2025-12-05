#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/functions/eval.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Nil {
    struct Object obj;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Nil* nil_new(void) {
    return (struct Nil*)object_new(OT_Nil, NWORDS(struct Nil));
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void nil_eval(struct Object* nil, struct Evaluator* etor) {
    fputs("foo_eval called\n", stderr);
}

void nil_show(struct Object* nil, FILE* stream) {
    fputs("nil\n", stream);
}

/* Private functions *********************************************************/

__attribute__((used, section("eval_function")))
static const struct EvalFunction_handler h_nil_eval = {OT_Nil, nil_eval};

__attribute__((used, section("show_function")))
static const struct ShowFunction_handler h_nil_show = {OT_Nil, nil_show};

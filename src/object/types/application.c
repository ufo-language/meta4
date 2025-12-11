#include <string.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/apply.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/application.h"
#include "object/types/identifier.h"
#include "object/types/array.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Application* application_new(struct Object* abstraction, count_t nArgs, struct Object* args[]) {
    struct Application* app = (struct Application*)object_new(OT_Application, NWORDS(*app) + nArgs);
    app->abstraction = abstraction;
    app->nArgs = nArgs;
    memcpy(app->args, args, sizeof(struct Object*) * nArgs);
    return app;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

bool_t application_eval(struct Application* app, struct Etor_rec* etor, struct Object** value) {
    /* Evaluate the abstraction */
    struct Object* abstrVal;
    if (!eval_rec(app->abstraction, etor, &abstrVal)) {
        return false;
    }
    /* Evaluate the arguments */
    struct Object** argVals = memory_alloc(app->nArgs);
    struct Object* argVal;
    for (index_t n=0; n<app->nArgs; n++) {
        if (!eval_rec(app->args[n], etor, &argVal)) {
            return false;
        }
        argVals[n] = argVal;
    }
    /* Apply the abstraction to the arguments */
    return apply(abstrVal, etor, app->nArgs, argVals, value);
}

void application_show(struct Application* app, FILE* stream) {
    struct Object* abstr = app->abstraction;
    if (abstr->typeId == OT_Identifier) {
        identifier_show((struct Identifier*)abstr, stream);
    }
    else {
        fputc('(', stream);
        show(abstr, stream);
        fputc(')', stream);
    }
    fputc('(', stream);
    array_showElems(app->nArgs, app->args, ", ", stream);
    fputc(')', stream);
}

#include <string.h>

#include "_typedefs.h"

#include "object/evaluator/etor_cps.h"
#include "object/types/continuation.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Continuation* contin_new(string_t name, void (*eval)(struct Continuation*, struct Etor_CPS)) {
    count_t nChars = strlen(name);
    struct Continuation* contin = (struct Continuation*)object_new(OT_Continuation, NWORDS(*contin) + NBYTES_TO_WORDS(nChars + 1));
    memcpy(contin->name, name, nChars + 1);
    contin->eval = eval;
    return contin;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void contin_eval_cps(struct Continuation* contin, struct Etor_CPS etor) {
    (void)contin;
    (void)etor;
}

void contin_show(struct Continuation* contin, struct OutStream* outStream) {
    (void)contin;
    (void)outStream;
}

/* Private functions *********************************************************/

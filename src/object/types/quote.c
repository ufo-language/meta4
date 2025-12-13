#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/quote.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Quote* quote_new(struct Object* expr) {
    struct Quote* quote = (struct Quote*)object_new(OT_Quote, NWORDS(*quote));
    quote->expr = expr;
    return quote;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t quote_eval_rec(struct Quote* quote, struct Etor_rec* etor, struct Object **value) {
    (void)etor;
    *value = quote->expr;
    return true;
}

void quote_show(struct Quote* quote, FILE* stream) {
    fputc('\'', stream);
    show(quote->expr, stream);
    fputc('\'', stream);
}

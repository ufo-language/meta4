#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/eval.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/integer.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Integer* integer_new(int_t i) {
    struct Integer* integer = (struct Integer*)object_new(OT_Integer, NWORDS(*integer));
    integer->i = i;
    return integer;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t integer_eval(struct Integer* integer, struct Evaluator* etor, struct Object** value) {
    *value = (struct Object*)integer;
    return true;
}

void integer_show(struct Integer* integer, FILE* stream) {
    fprintf(stream, "%ld", integer->i);
}

/* Private functions *********************************************************/

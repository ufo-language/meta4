#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/intvar.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct IntVar* intVar_new(int_t i) {
    struct IntVar* intVar = (struct IntVar*)object_new(OT_IntVar, NWORDS(*intVar));
    intVar->i = i;
    return intVar;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t intVar_equal(struct IntVar* intVar, struct IntVar* other) {
    return intVar->i == other->i;
}

void intVar_show(struct IntVar* intVar, FILE* stream) {
    fprintf(stream, "IntVar{%ld}", intVar->i);
}

/* Private functions *********************************************************/

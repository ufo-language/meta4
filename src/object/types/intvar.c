#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/intvar.h"
#include "object/types/outstream.h"

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

void intVar_show(struct IntVar* intVar, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'S', "IntVar{",
        'I', intVar->i,
        'C', '}',
        0);
}

/* Private functions *********************************************************/

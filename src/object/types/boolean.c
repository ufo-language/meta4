#include <stdio.h>

#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/boolean.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Boolean* boolean_new(bool_t b) {
    struct Boolean* boolean = (struct Boolean*)object_new(OT_Boolean, NWORDS(*boolean));
    boolean->b = b;
    return boolean;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void boolean_show(struct Boolean* boolean, struct OutStream* outStream) {
    outStream_writeString(outStream, boolean->b ? "true" : "false");
}

/* Private functions *********************************************************/

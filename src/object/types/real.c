#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/real.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Real* real_new(real_t r) {
    struct Real* real = (struct Real*)object_new(OT_Real, NWORDS(*real));
    real->r = r;
    return real;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t real_equal(struct Real* real, struct Real* other) {
    return real->r == other->r;
}

void real_show(struct Real* real, FILE* stream) {
    fprintf(stream, "%lf", real->r);
}

/* Private functions *********************************************************/

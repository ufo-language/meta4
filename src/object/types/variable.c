#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/outstream.h"
#include "object/types/variable.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Variable* variable_new(struct Object* value) {
    struct Variable* var = (struct Variable*)object_new(OT_Var, NWORDS(*var));
    var->value = value;
    return var;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void variable_show(struct Variable* var, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'S', "Var{",
        'O', var->value,
        'C', '}',
        0);
}

/* Private functions *********************************************************/

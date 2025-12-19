#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/outstream.h"
#include "object/types/var.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Var* var_new(struct Object* value) {
    struct Var* var = (struct Var*)object_new(OT_Var, NWORDS(*var));
    var->value = value;
    return var;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void var_show(struct Var* var, struct OutStream* outStream) {
    outStream_fwrite(outStream,
        'S', "Var{",
        'O', var->value,
        'C', '}',
        0
    );
}

/* Private functions *********************************************************/

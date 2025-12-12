#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/function.h"
#include "object/types/primitive.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t apply(struct Object* obj, struct Etor_rec* etor, count_t nArgs, struct Object* args[], struct Object** value) {
    switch (obj->typeId) {
        case OT_Function:  return function_apply((struct Function*)obj, etor, nArgs, args, value);
        case OT_Primitive: return prim_apply((struct Primitive*)obj, etor, nArgs, args, value);
        default:
            return false;
    }
}

/* Private functions *********************************************************/

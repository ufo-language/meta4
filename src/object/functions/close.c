#include "_typedefs.h"

#include "object/functions/eval.h"
#include "object/object.h"
#include "object/types/evaluator.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t close(struct Object* obj, struct Evaluator* etor, struct Object** value) {
    etor->operationType = Etor_Closing;
    bool_t success = eval(obj, etor, value);
    etor->operationType = Etor_Evaluating;
    return success;
}

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/functions/eval_recursive.h"
#include "object/object.h"
#include "object/evaluator/evaluator_recursive.h"
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
    bool_t success = eval_recursive(obj, etor, value);
    etor->operationType = Etor_Evaluating;
    return success;
}

/* Private functions *********************************************************/

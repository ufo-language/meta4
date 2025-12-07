#include "_typedefs.h"

#include "object/functions/eval_rec.h"
#include "object/object.h"
#include "object/evaluator/etor_rec.h"
/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t close(struct Object* obj, struct Etor_Rec* etor, struct Object** value) {
    etor->evaluationType = Etor_Closing;
    bool_t success = eval_rec(obj, etor, value);
    etor->evaluationType = Etor_Evaluating;
    return success;
}

/* Private functions *********************************************************/

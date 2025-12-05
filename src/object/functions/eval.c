#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/typeids.h"
#include "object/types/evaluator.h"
#include "object/functions/eval.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

EvalFunction2 g_evalFunctions[OT_Max];

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void eval(struct Object* obj, struct Evaluator* etor) {
    g_evalFunctions[obj->typeId](obj, etor);
}

/* Private functions *********************************************************/

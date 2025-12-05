#include "object/typeids.h"

struct Evaluator;
struct Object;

/* Defines *******************************************************************/

/* Types *********************************************************************/

typedef void (*EvalFunction2)(struct Object* obj, struct Evaluator* etor);

struct EvalFunction_handler2 {
    enum TypeID typeId;
    EvalFunction2 function;
};

typedef void (*EvalFunction)(struct Object* obj, struct Evaluator* etor);

struct EvalFunction_handler {
    enum TypeID typeId;
    EvalFunction function;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

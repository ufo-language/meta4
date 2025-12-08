#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/globals.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Function {
    struct Object obj;
    struct Identifier* name;
    struct Object* body;
    struct Object* closedBody;
    struct Function* nextRule;
    count_t nParams;
    struct Object* params[];
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Function* function_new(struct Identifier* name, count_t nParams, struct Object* params[], struct Object* body, struct Function* nextRule);
struct Function* function_new_empty(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t function_close_rec(struct Function* function, struct Etor_Rec* etor, struct Object** value);
bool_t function_eval_rec(struct Function* function, struct Etor_Rec* etor, struct Object** value);
void function_show(struct Function* function, FILE* stream);

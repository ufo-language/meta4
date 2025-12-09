#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Dec {
    struct Object obj;
    struct Object* expr;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Dec* dec_new(struct Object* expr);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t dec_eval_rec(struct Dec* dec, struct Etor_rec* etor, struct Object** value);
void dec_show(struct Dec* dec, FILE* stream);

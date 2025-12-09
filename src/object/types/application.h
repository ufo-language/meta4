#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Application {
    struct Object obj;
    struct Object* abstraction;
    count_t nArgs;
    struct Object* args[];
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Application* application_new(struct Object* abstraction, count_t nArgs, struct Object* args[]);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t application_eval(struct Application* app, struct Etor_rec* etor, struct Object** value);

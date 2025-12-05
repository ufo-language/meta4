#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Array {
    struct Object obj;
    count_t nElems;
    struct Object* elems[];
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Array* array_new(count_t nElems, struct Object* elems[]);
struct Array* array_new_fill(count_t nElems, struct Object* elem);
struct Array* array_new_nofill(count_t nElems);
void array_init(struct Array* array, count_t nElems, struct Object* elems[]);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t array_eval(struct Array* array, struct Evaluator* etor, struct Object** value);

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Symbolic {
    struct Object obj;
    word_t hashCode;
    char name[];
};

enum TypeId;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* symbolic_new(const string_t name, enum TypeId typeId, struct Vector* internTable);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

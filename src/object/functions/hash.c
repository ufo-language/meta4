#include "_typedefs.h"

#include "object/object.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t hash(struct Object* obj, word_t* hashCode) {
    switch (obj->typeId) {
        case OT_Identifier:
        case OT_Symbol:
            *hashCode = ((struct Symbolic*)obj)->hashCode;
            return true;
        case OT_String:
            return string_hash((struct String*)obj, hashCode);
        default:
            return false;
    }
}

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "object/functions/hash.h"
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
        case OT_Identifier: *hashCode = ((struct Symbolic*)obj)->hashCode; return true;
        case OT_String:     *hashCode = string_hash((struct String*)obj, hashCode); return true;
        case OT_Symbol:     *hashCode = ((struct Symbolic*)obj)->hashCode; return true;
        default:            return false;
    }
}

/* Private functions *********************************************************/

#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/display.h"
#include "object/functions/show.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void display(struct Object* obj, struct OutStream* outStream) {
    switch(obj->typeId) {
        case OT_Nil:
            return;  /* nil is not displayed */
        case OT_String:
            string_display((struct String*)obj, outStream);
            return;
        default:
            show(obj, outStream);
            break;
    }
}

/* Private functions *********************************************************/

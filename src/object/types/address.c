#include "_typedefs.h"

#include "object/types/address.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Address* address_new(void* addr) {
    struct Address* address = (struct Address*)object_new(OT_Address, NWORDS(*address));
    address->address = addr;
    return address;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void address_show(struct Address* address, struct OutStream* outStream) {
    fprintf(outStream->file, "%p", address->address);
}

/* Private functions *********************************************************/

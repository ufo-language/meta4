#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/functions/hash.h"
#include "object/typeids.h"
#include "object/types/nil.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Nil* nil_new(void) {
    return (struct Nil*)object_new(OT_Nil, NWORDS(struct Nil));
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t nil_eval_rec(struct Nil* nil, struct Etor_rec* etor, struct Object** value) {
    (void)etor;
    *value = (struct Object*)nil;
    return true;
}

bool_t nil_hash(struct Nil* nil, word_t* hashCode) {
    hash_objHeader((struct Object*)nil, hashCode);
    return true;
}

void nil_show(struct Nil* nil, struct OutStream* outStream) {
    (void)nil;
    outStream_writeString(outStream, "nil");
}

/* Private functions *********************************************************/

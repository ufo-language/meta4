#include <assert.h>
#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/count.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/bytebuffer.h"
#include "object/types/hashtable.h"
#include "object/types/instream.h"
#include "object/types/intarray.h"
#include "object/types/intvector.h"
#include "object/types/pair.h"
#include "object/types/string.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

bool_t count(struct Object* obj, count_t* nElems) {
    switch(obj->typeId) {
        case OT_Array:      *nElems = ((struct Array*)obj)->nElems; return true;
        case OT_ByteBuffer: *nElems = byteBuffer_count((struct ByteBuffer*)obj); return true;
        case OT_HashTable:  *nElems = ((struct HashTable*)obj)->nElems; return true;
        case OT_IntArray:   *nElems = ((struct IntArray*)obj)->nElems; return true;
        case OT_InStream:   *nElems = inStream_available((struct InStream*)obj); return true;
        case OT_IntVector:  *nElems = ((struct IntVector*)obj)->nElems; return true;
        case OT_Pair:       *nElems = pair_count((struct Pair*)obj); return true;
        case OT_String:     *nElems = ((struct String*)obj)->nChars; return true;
        case OT_Term:       *nElems = 1 + ((struct Term*)obj)->nArgs; return true;
        case OT_Vector:     *nElems = ((struct Vector*)obj)->nElems; return true;
        default:            return false;
    }
    fprintf(stderr, "count: Unhandled type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    assert(false);
    return false;
}

/* Private functions *********************************************************/

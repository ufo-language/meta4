#include "_typedefs.h"

#include "object/functions/hash.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/boolean.h"
#include "object/types/integer.h"
#include "object/types/primitive.h"
#include "object/types/real.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

void hash_bytes(count_t nBytes, const void* payload, word_t* hashCode) {
    const unsigned char* bytes = payload;
    for (size_t n=0; n<nBytes; n++) {
        *hashCode ^= bytes[n];
        *hashCode *= FNV_Prime;
    }
}

void hash_obj(struct Object* obj, count_t nPayloadBytes, const void* payload, word_t* hashCode) {
    word_t h = *hashCode;
    /* Hash the object header */
    hash_objHeader(obj, hashCode);
    /* Hash the object payload */
    hash_bytes(nPayloadBytes, payload, &h);
    *hashCode = h;
}

void hash_objHeader(struct Object* obj, word_t* hashCode) {
    hash_bytes(sizeof(enum TypeId), &obj->typeId, hashCode);
    hash_bytes(sizeof(count_t), &obj->nWords, hashCode);
}

bool_t hash_rec(struct Object* obj, word_t* hashCode) {
    switch (obj->typeId) {
        case OT_Boolean:    hash_obj(obj, sizeof(bool_t), &((struct Boolean*)obj)->b, hashCode);
        case OT_Identifier: *hashCode = ((struct Symbolic*)obj)->hashCode; return true;
        case OT_Integer:    hash_obj(obj, sizeof(int_t), &((struct Integer*)obj)->i, hashCode); return true;
        case OT_Primitive:  return prim_hash((struct Primitive*)obj, hashCode);
        case OT_Real:       hash_obj(obj, sizeof(real_t), &((struct Real*)obj)->r, hashCode); return true;
        case OT_String:     hash_obj(obj, ((struct String*)obj)->nChars, ((struct String*)obj)->chars, hashCode); return true;
        case OT_Symbol:     *hashCode = ((struct Symbolic*)obj)->hashCode; return true;
        /* The remaining objects are not hashable */
        default:
            return false;
    }
}

/* Object functions ******************/

bool_t hash(struct Object* obj, word_t* hashCode) {
    *hashCode = FNV_Offset;
    return hash_rec(obj, hashCode);
}

/* Private functions *********************************************************/

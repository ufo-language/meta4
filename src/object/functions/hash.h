#pragma once

#include "_typedefs.h"

#include "object/typeids.h"

/* Defines *******************************************************************/

#define FNV_Offset 1469598103934665603ULL
#define FNV_Prime 1099511628211ULL

/* Types *********************************************************************/

struct Object;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

void hash_bytes(count_t nBytes, const void* payload, word_t* hashCode);
bool_t hash_rec(struct Object* obj, word_t* hashCode);
void hash_obj(struct Object* obj, count_t nPayloadBytes, const void* payload, word_t* hashCode);
void hash_objHeader(struct Object* obj, word_t* hashCode);

/* Object functions ******************/

bool_t hash(struct Object* obj, word_t* hashCode);

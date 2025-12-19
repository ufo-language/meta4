#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Symbolic {
    struct Object obj;
    word_t hashCode;
    char name[];
};

struct HashTable;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Symbolic* symbolic_new(const string_t name, enum TypeId typeId, struct HashTable* internTable);
struct Symbolic* symbolic_new_aux(enum TypeId typeId, count_t nChars, const string_t name, word_t hashCode);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void symbolic_show(struct Symbolic* symbolic, FILE* stream);

/* Private functions *********************************************************/

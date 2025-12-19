#include <stdio.h>

#include "_typedefs.h"

#include "object/types/hashtable.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Set {
    struct HashTable hashTable;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Set* set_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void set_add(struct Set* set, struct Object* elem);
bool_t set_contains(struct Set* set, struct Object* elem);
bool_t set_remove(struct Set* set, struct Object* elem);

/* Object functions ******************/

count_t set_count(struct Set* set);
void set_show(struct Set* set, struct OutStream* outStream);

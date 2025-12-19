#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Pair;

struct Queue {
    struct Object obj;
    struct Pair* first;
    struct Pair* last;
    count_t nElems;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Queue* queue_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void queue_enq(struct Queue* q, struct Object* elem);
bool_t queue_deq(struct Queue* q, struct Object** elem);

/* Object functions ******************/

count_t queue_count(struct Queue* q);
void queue_show(struct Queue* q, FILE* stream);

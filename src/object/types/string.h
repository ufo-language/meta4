#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct String {
    struct Object obj;
    count_t nChars;
    string_t chars;
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct String* string_new(const string_t chars);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void string_display(struct String* string, FILE* stream);
bool_t string_equal(struct String* string, struct String* other);
void string_show(struct String* string, FILE* stream);
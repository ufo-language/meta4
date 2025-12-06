#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct String* string_new(const string_t chars) {
    count_t nChars = strlen(chars);
    struct String* string = (struct String*)object_new(OT_String, NWORDS(*string) + NWORDS_FROM_BYTES(nChars + 1));
    string->nChars = nChars;
    strcpy(string->chars, chars);
    return string;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void string_display(struct String* string, FILE* stream) {
    fputs(string->chars, stream);
}

bool_t string_equal(struct String* string, struct String* other) {
    return strcmp(string->chars, other->chars) == 0;
}

void string_show(struct String* string, FILE* stream) {
    fputc('"', stream);
    string_t chars = string->chars;
    for (char c=*chars; c; chars++) {
        switch (c) {
            case '\n': fputs("\\n", stream); break;
            case '\r': fputs("\\r", stream); break;
            case '\t': fputs("\\t", stream); break;
            case '\\': fputs("\\\\", stream); break;
            default:
                fputc(c, stream);
                break;
        }
    }
    fputc('"', stream);
}

/* Private functions *********************************************************/

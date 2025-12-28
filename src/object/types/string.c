#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/functions/compare.h"
#include "object/object.h"
#include "object/types/outstream.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct String* string_new(const string_t chars) {
    count_t nChars = strlen(chars);
    struct String* string = string_new_empty(nChars);
    // string->nChars = nChars;
    // memcpy(string->chars, chars, nChars + 1);
    string_init(string, nChars, chars);
    return string;
}

struct String* string_new_empty(count_t nChars) {
    struct String* string = (struct String*)object_new(OT_String, NWORDS(*string) + NBYTES_TO_WORDS(nChars + 1));
    /* This is duplicated in string_init; that's necessary because these functions
       are used in other places */
    string->nChars = nChars;  
    return string;
}

void string_init(struct String* string, count_t nChars, const string_t chars) {
    object_init((struct Object*)string, OT_String, NWORDS(*string) + NBYTES_TO_WORDS(nChars + 1));
    /* This is duplicated in string_new_empty; that's necessary because these functions
       are used in other places */
    string->nChars = nChars;
    memcpy(string->chars, chars, nChars + 1);  /* The '+ 1' copies the null terminator */
}

/* Public functions **********************************************************/

/* Unique functions ******************/

// bool_t string_equal_chars(struct String* string, string_t chars) {
//     return strcmp(string->chars, chars) == 0;
// }

enum CompareResult string_compare_chars(string_t string, string_t otherString) {
    int res = strcmp(string, otherString);
    if (res < 0) return CompareLess;
    if (res > 0) return CompareGreater;
    return CompareEqual;
}

/* Object functions ******************/

enum CompareResult string_compare(struct String* string, struct String* otherString) {
    return string_compare_chars(string->chars, otherString->chars);
}

void string_display(struct String* string, struct OutStream* outStream) {
    outStream_writeString(outStream, string->chars);
}

bool_t string_equal(struct String* string, struct String* other) {
    return strcmp(string->chars, other->chars) == 0;
}

bool_t string_hash(struct String* string, word_t* hashCode) {
    return string_hash_chars(OT_String, string->nChars, string->chars, hashCode);
}

bool_t string_hash_chars(enum TypeId typeId, count_t nChars, const string_t chars, word_t* hashCode) {
    word_t h = 1469598103934665603ULL;   /* FNV-1a offset (64-bit) */
    h ^= typeId;
    h *= 1099511628211ULL;
    for (count_t i = 0; i < nChars; ++i) {
        h ^= (word_t)chars[i];
        h *= 1099511628211ULL;  /* FNV prime */
    }
    *hashCode = h;
    return true;
}

void string_show(struct String* string, struct OutStream* outStream) {
    outStream_writeChar(outStream, '"');
    for (char *p=string->chars; *p; ++p) {
        char c = *p;
        switch (c) {
            case '\n': outStream_writeString(outStream, "\\n"); break;
            case '\r': outStream_writeString(outStream, "\\r"); break;
            case '\t': outStream_writeString(outStream, "\\t"); break;
            case '\\': outStream_writeString(outStream, "\\\\"); break;
            case '"':  outStream_writeString(outStream, "\\\""); break;
            default:
                if ((unsigned char)c < 0x20 || c == 0x7F)
                    outStream_writeHexInt(outStream, c);
                else
                    outStream_writeChar(outStream, c);
                break;
        }
    }
    outStream_writeChar(outStream, '"');
}

/* Private functions *********************************************************/

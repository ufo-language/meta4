#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/compare.h"
#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct String {
    struct Object obj;
    count_t nChars;
    char chars[];
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct String* string_new(const string_t chars);
struct String* string_new_empty(count_t nChars);
void string_init(struct String* string, count_t nChars, const string_t chars);

/* Public functions **********************************************************/

/* Unique functions ******************/

enum CompareResult string_compare_chars(string_t string, string_t otherString);
bool_t string_hash_chars(enum TypeId typeId, count_t nChars, const string_t chars, word_t* hashCode);

/* Object functions ******************/

enum CompareResult string_compare(struct String* string, struct String* otherString);
void string_display(struct String* string, struct OutStream* outStream);
bool_t string_equal(struct String* string, struct String* other);
bool_t string_hash(struct String* string, word_t* hashCode);
void string_show(struct String* string, struct OutStream* outStream);

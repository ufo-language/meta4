#pragma once

#include <stdint.h>

/* The two types count_t and index_t are inherently the same, but the
   role they play is different.
       count_t is for cardinal numbers
       index_t is for ordinal numbers, but 0-based because this is C
   The two types will sometimes be mixed (usually by taking a sum).
*/
typedef __SIZE_TYPE__ count_t;
typedef __SIZE_TYPE__ index_t;
#define COUNT_MAX     SIZE_MAX
#define INDEX_MAX     SIZE_MAX

/* These all have machine-word width. */
typedef void*         address_t;
typedef intptr_t      int_t;
typedef uintptr_t     uint_t;
typedef uintptr_t     word_t;
typedef double        real_t;

typedef uint8_t       byte_t;

typedef int           ichar_t;
typedef char*         string_t;

typedef int           bool_t;
#define true 1
#define false 0

#define NWORDS(type) (sizeof(type) / sizeof(word_t))
#define NBYTES_TO_WORDS(nBytes) (((nBytes) + sizeof(word_t) - 1) / sizeof(word_t))

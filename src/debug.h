#pragma once

#include <stdio.h>

#include "object/functions/show.h"

#define DEBUG0(string1) \
    fputs(string1, stderr); \
    fputc('\n', stderr)

#define DEBUG1(string1, object1) \
    fputs(string1, stderr); \
    show((struct Object*)object1, stderr); \
    fputc('\n', stderr)

#define DEBUG2(string1, object1, string2, object2) \
    fputs(string1, stderr); \
    show((struct Object*)object1, stderr); \
    fputs(string2, stderr); \
    show((struct Object*)object2, stderr); \
    fputc('\n', stderr)

#define DEBUG_ARRAY(string1, nElems, array) \
    fputs(string1, stderr); \
    fprintf(stderr, "(%lu elems)\n", nElems); \
    for (size_t n=0; n<nElems; ++n) { \
        fprintf(stderr, "    [%lu] ", n); \
        show(array[n], stderr); \
        fputc('\n', stderr); \
    }

#define PAUSE() fputs("Press a key ", stderr); getchar()
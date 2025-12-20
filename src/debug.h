#pragma once

#include <stdio.h>

#include "object/globals.h"
#include "object/types/outstream.h"
#include "object/functions/show.h"

#define DEBUG0(string1) \
    outStream_fwriteLn(g_stderr, \
        'S', string1, \
        0);

#define DEBUG1(string1, object1) \
    outStream_fwriteLn(g_stderr, \
        'S', string1, \
        'O', (struct Object*)object1, \
        0);

#define DEBUG2(string1, object1, string2, object2) \
    outStream_fwriteLn(g_stderr, \
        'S', string1, \
        'O', (struct Object*)object1, \
        'S', string2, \
        'O', (struct Object*)object2, \
        0);

#define DEBUG_ARRAY(string1, nElems, array) \
    fputs(string1, stderr); \
    fprintf(stderr, "(%lu elems)\n", nElems); \
    for (size_t n=0; n<nElems; ++n) { \
        fprintf(stderr, "    [%lu] ", n); \
        show(array[n], g_stderr); \
        fputc('\n', stderr); \
    }

#define PAUSE() fputs("Press a key ", stderr); getchar()

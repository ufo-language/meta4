#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "object/functions/equal.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/bytebuffer.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

#define DEFAULT_BYTE_BUFFER_SIZE 8

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _resize(struct ByteBuffer* byteBuffer);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ByteBuffer* byteBuffer_new(void) {
    struct ByteBuffer* byteBuffer = (struct ByteBuffer*)object_new(OT_ByteBuffer, NWORDS(*byteBuffer));
    byteBuffer->capacity = DEFAULT_BYTE_BUFFER_SIZE;
    byteBuffer->nBytes = 0;
    gc_pushRoot(g_gc, (struct Object*)byteBuffer);
    byteBuffer->bytes = memory_alloc(NBYTES_TO_WORDS(DEFAULT_BYTE_BUFFER_SIZE));
    gc_popRoot(g_gc);
    return byteBuffer;
}

/* Public functions **********************************************************/

void byteBuffer_appendByte(struct ByteBuffer* byteBuffer, byte_t byte) {
    if (byteBuffer->nBytes == byteBuffer->capacity) {
        _resize(byteBuffer);
    }
    byteBuffer->bytes[byteBuffer->nBytes++] = byte;
}

void byteBuffer_appendBytes(struct ByteBuffer* byteBuffer, count_t nBytes, byte_t bytes[]) {
    while (byteBuffer->nBytes + nBytes >= byteBuffer->capacity) {
        _resize(byteBuffer);
    }
    memcpy(byteBuffer->bytes + byteBuffer->nBytes, bytes, nBytes);
    byteBuffer->nBytes += nBytes;
}

/* Unique functions ******************/

count_t byteBuffer_capacity(struct ByteBuffer* byteBuffer) {
    return byteBuffer->capacity;
}

struct String* byteBuffer_toString(struct ByteBuffer* byteBuffer) {
    count_t nBytes = byteBuffer->nBytes;
    struct String* string = string_new_empty(nBytes);
    memcpy(string->chars, byteBuffer->bytes, nBytes);
    string->chars[nBytes] = 0;
    return string;
}

/* Object functions ******************/

count_t byteBuffer_count(struct ByteBuffer* byteBuffer) {
    return byteBuffer->nBytes;
}

void byteBuffer_show(struct ByteBuffer* byteBuffer, FILE* stream) {
    fputs("ByteBuffer{", stream);
    count_t nBytes = byteBuffer->nBytes;
    byte_t* bytes = byteBuffer->bytes;
    for (count_t n=0; n<nBytes; ++n) {
        if (n > 0) {
            fputs(", ", stream);
        }
        fprintf(stream, "%2X", bytes[n]);
    }
    fputc('}', stream);
}

/* Private functions *********************************************************/

static void _resize(struct ByteBuffer* byteBuffer) {
    count_t nBytes = byteBuffer->nBytes;
    count_t newCapacity = byteBuffer->capacity * 2;
    byte_t* newBytes = memory_alloc(NBYTES_TO_WORDS(newCapacity));
    memcpy(newBytes, byteBuffer->bytes, nBytes);
    byteBuffer->capacity = newCapacity;
    ++byteBuffer->nResizes;
}

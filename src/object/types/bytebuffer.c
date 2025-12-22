#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/gc.h"
#include "memory/memory.h"
#include "object/globals.h"
#include "object/functions/equal.h"
#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/bytebuffer.h"
#include "object/types/outstream.h"
#include "object/types/string.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _byteBuffer_resize(struct ByteBuffer* byteBuffer);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ByteBuffer* byteBuffer_new(void) {
    struct ByteBuffer* byteBuffer = (struct ByteBuffer*)object_new(OT_ByteBuffer, NWORDS(*byteBuffer));
    byteBuffer->capacity = ByteBuffer_DefaultCapacity;
    // byteBuffer->nBytes = 0;
    byteBuffer->writeIndex = 0;
    gc_pushRoot(g_gc, (struct Object*)byteBuffer);
    byteBuffer->bytes = memory_alloc(NBYTES_TO_WORDS(ByteBuffer_DefaultCapacity));
    gc_popRoot(g_gc);
    return byteBuffer;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void byteBuffer_appendByte(struct ByteBuffer* byteBuffer, byte_t byte) {
    if (byteBuffer->writeIndex == byteBuffer->capacity) {
        _byteBuffer_resize(byteBuffer);
    }
    byteBuffer->bytes[byteBuffer->writeIndex++] = byte;
    ++byteBuffer->nBytes;
}

void byteBuffer_appendBytes(struct ByteBuffer* byteBuffer, count_t nBytes, byte_t bytes[]) {
    while (byteBuffer->writeIndex + nBytes >= byteBuffer->capacity) {
        _byteBuffer_resize(byteBuffer);
    }
    memcpy(byteBuffer->bytes + byteBuffer->writeIndex, bytes, nBytes);
    byteBuffer->writeIndex += nBytes;
    byteBuffer->nBytes += nBytes;
}

bool_t byteBuffer_readByte(struct ByteBuffer* byteBuffer, byte_t* byte) {
    if (byteBuffer->nBytes == 0) {
        return false;
    }
    *byte = byteBuffer->bytes[byteBuffer->readIndex++];
    if (--byteBuffer->nBytes == 0) {
        /* If there are no bytes left, set both indexes back to 0. */
        byteBuffer->writeIndex = byteBuffer->readIndex = 0;
    }
    return true;
}

/* Note that if the byteBuffer contains embedded 0s then the string will also
   contain embedded 0s. */
bool_t byteBuffer_readString(struct ByteBuffer* byteBuffer, struct String** string) {
    if (byteBuffer->nBytes == 0) {
        return false;
    }
    count_t nBytes = byteBuffer->nBytes;
    *string = string_new_empty(nBytes);
    memcpy((*string)->chars, byteBuffer->bytes, nBytes);
    (*string)->chars[nBytes] = 0;
    byteBuffer->nBytes = 0;
    byteBuffer->writeIndex = 0;
    byteBuffer->readIndex = 0;
    return true;
}

/* Object functions ******************/

count_t byteBuffer_count(struct ByteBuffer* byteBuffer) {
    return byteBuffer->nBytes;
}

void byteBuffer_show(struct ByteBuffer* byteBuffer, struct OutStream* outStream) {
    outStream_writeString(outStream, "ByteBuffer{");
    count_t nBytes = byteBuffer->nBytes;
    byte_t* bytes = byteBuffer->bytes;
    for (count_t n=0; n<nBytes; ++n) {
        if (n > 0) {
            outStream_writeString(outStream, ":");
        }
        outStream_writeHexInt(outStream, bytes[n]);
    }
    outStream_writeChar(outStream, '}');
}

/* Private functions *********************************************************/

static void _byteBuffer_resize(struct ByteBuffer* byteBuffer) {
    count_t nBytes = byteBuffer->nBytes;
    if (nBytes <= byteBuffer->capacity / 2) {
        /* If the nBtes <= 1/2 the capacity, don't reallocate, just shift */
        memcpy(byteBuffer->bytes, &byteBuffer->bytes[byteBuffer->readIndex], nBytes);
        byteBuffer->writeIndex = nBytes;
        byteBuffer->readIndex = 0;
    }
    else {
        count_t newCapacity = byteBuffer->capacity * 2;
        byte_t* newBytes = memory_alloc(NBYTES_TO_WORDS(newCapacity));
        memcpy(newBytes, &byteBuffer->bytes[byteBuffer->readIndex], nBytes);
        byteBuffer->capacity = newCapacity;
        byteBuffer->writeIndex = nBytes;
        byteBuffer->readIndex = 0;
        ++byteBuffer->nResizes;
    }
}

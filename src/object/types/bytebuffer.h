#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum {
    DEFAULT_BYTE_BUFFER_SIZE = 8
};

struct ByteBuffer {
    struct Object obj;
    count_t capacity;
    count_t nBytes;
    byte_t* bytes;
    count_t nResizes;
};

struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ByteBuffer* byteBuffer_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void byteBuffer_appendByte(struct ByteBuffer* byteBuffer, byte_t byte);
void byteBuffer_appendBytes(struct ByteBuffer* byteBuffer, count_t nBytes, byte_t bytes[]);
struct String* byteBuffer_toString(struct ByteBuffer* byteBuffer);

/* Object functions ******************/

void byteBuffer_show(struct ByteBuffer* byteBuffer, struct OutStream* outStream);

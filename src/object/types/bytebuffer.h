#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum {
    ByteBuffer_DefaultCapacity = 8
};

struct ByteBuffer {
    struct Object obj;
    count_t capacity;
    count_t nBytes;
    index_t writeIndex;
    index_t readIndex;
    count_t nResizes;
    byte_t* bytes;
};

struct OutStream;
struct String;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ByteBuffer* byteBuffer_new(void);

/* Public functions **********************************************************/

/* Unique functions ******************/

void byteBuffer_appendByte(struct ByteBuffer* byteBuffer, byte_t byte);
void byteBuffer_appendBytes(struct ByteBuffer* byteBuffer, count_t nBytes, byte_t bytes[]);
count_t byteBuffer_count(struct ByteBuffer* byteBuffer);
count_t byteBuffer_moveBytesTo(struct ByteBuffer* byteBuffer, struct ByteBuffer* otherByteBuffer);
bool_t byteBuffer_readByte(struct ByteBuffer* byteBuffer, byte_t* byte);
bool_t byteBuffer_readString(struct ByteBuffer* byteBuffer, struct String** string);

/* Object functions ******************/

void byteBuffer_show(struct ByteBuffer* byteBuffer, struct OutStream* outStream);

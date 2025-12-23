#pragma once

#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum InStreamType {
    IST_File, IST_ByteBuffer
};

struct ByteBuffer;

struct InStream {
    struct Object obj;
    enum InStreamType streamType;
    union {
        FILE* file;
        struct ByteBuffer* byteBuffer;
    };
};

struct OutStream;
struct String;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct InStream* inStream_new_file(FILE* file);
struct InStream* inStream_new_byteBuffer(struct ByteBuffer* byteBuffer);

/* Public functions **********************************************************/

/* Unique functions ******************/

count_t inStream_available(struct InStream* inStream);
bool_t inStream_readByte(struct InStream* inStream, byte_t* byte);
count_t inStream_readBytes(struct InStream* inStream, struct ByteBuffer* buffer);
bool_t inStream_readLine(struct InStream* inStream, struct String** string);
bool_t inStream_readString(struct InStream* inStream, struct String** string);

/* Object functions ******************/

void inStream_show(struct InStream* inStream, struct OutStream* outStream);

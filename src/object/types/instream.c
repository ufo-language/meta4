#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "object/object.h"
#include "object/types/bytebuffer.h"
#include "object/types/instream.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static void _inStream_streamTypeError(enum InStreamType ist);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct InStream* inStream_new_file(FILE* file) {
    struct InStream* inStream = (struct InStream*)object_new(OT_InStream, NWORDS(struct InStream));
    inStream->file = file;
    inStream->streamType = IST_File;
    return inStream;
}

struct InStream* inStream_new_byteBuffer(struct ByteBuffer* byteBuffer) {
    struct InStream* inStream = (struct InStream*)object_new(OT_InStream, NWORDS(struct InStream));
    inStream->byteBuffer = byteBuffer;
    inStream->streamType = IST_ByteBuffer;
    return inStream;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

count_t inStream_available(struct InStream* inStream) {
    switch (inStream->streamType) {
        case IST_ByteBuffer:
            return byteBuffer_count(inStream->byteBuffer);
        case IST_File:
            assert(false);
            break;
        default:
            _inStream_streamTypeError(inStream->streamType);
            break;
    }
}

bool_t inStream_readByte(struct InStream* inStream, byte_t* byte) {
    switch (inStream->streamType) {
        default:
            _inStream_streamTypeError(inStream->streamType);
            return false;
    }
}

count_t inStream_readBytes(struct InStream* inStream, struct ByteBuffer* buffer) {
    switch (inStream->streamType) {
        default:
            _inStream_streamTypeError(inStream->streamType);
            return 0;
    }
}

bool_t inStream_readString(struct InStream* inStream, struct String** string) {
    switch (inStream->streamType) {
        default:
            _inStream_streamTypeError(inStream->streamType);
            return false;
    }
}

/* Object functions ******************/

void inStream_show(struct InStream* inStream, struct OutStream* outStream) {
    outStream_writeString(outStream, "InStream{");
    switch (inStream->streamType) {
        default:
            break;
    }
    outStream_writeChar(outStream, '}');
}

/* Private functions *********************************************************/

static void _inStream_streamTypeError(enum InStreamType ist) {
    fprintf(stderr, "ERROR: unknown InStream type %d\n", ist);
    assert(false);
    exit(1);
}

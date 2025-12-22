#include <stdarg.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/types/bytebuffer.h"
#include "object/types/outstream.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

void _outStream_fwriteList(struct OutStream* outStream, va_list args);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct OutStream* outStream_new_file(FILE* file) {
    struct OutStream* outStream = (struct OutStream*)object_new(OT_OutStream, NWORDS(struct OutStream));
    outStream->streamType = OST_File;
    outStream->file = file;
    return outStream;
}

struct OutStream* outStream_new_byteBuffer(struct ByteBuffer* byteBuffer) {
    struct OutStream* outStream = (struct OutStream*)object_new(OT_OutStream, NWORDS(struct OutStream));
    outStream->streamType = OST_ByteBuffer;
    outStream->byteBuffer = byteBuffer;
    return outStream;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void outStream_nl(struct OutStream* outStream) {
    outStream_writeChar(outStream, '\n');
}

void outStream_fwrite(struct OutStream* outStream, ...) {
    va_list args;
    va_start(args, outStream);
    _outStream_fwriteList(outStream, args);
    va_end(args);
}

void outStream_fwriteLn(struct OutStream* outStream, ...) {
    va_list args;
    va_start(args, outStream);
    _outStream_fwriteList(outStream, args);
    va_end(args);
    outStream_nl(outStream);
}

void outStream_writeChar(struct OutStream* outStream, char c) {
    switch (outStream->streamType) {
        case OST_File:
            fputc(c, outStream->file);
            break;
        case OST_ByteBuffer:
            byteBuffer_appendByte(outStream->byteBuffer, c);
            break;
        default:
            assert(false);
            break;
    }
}

void outStream_writeString(struct OutStream* outStream, const string_t s) {
    switch (outStream->streamType) {
        case OST_File:
            fputs(s, outStream->file);
            break;
        case OST_ByteBuffer: {
                count_t nBytes = strlen(s);
                byteBuffer_appendBytes(outStream->byteBuffer, nBytes, (byte_t*)s);
            }
            break;
        default:
            assert(false);
            break;
    }
}

void outStream_writeInt(struct OutStream* outStream, int_t i) {
    char buffer[21];  /* Max chars for 64-bit integer */
    sprintf(buffer, "%ld", i);
    outStream_writeString(outStream, buffer);
}

void outStream_writeHexInt(struct OutStream* outStream, uint_t i) {
    char buffer[17];  /* Max chars for 64-bit hexadecimal integer */
    sprintf(buffer, "%lX", i);
    outStream_writeString(outStream, buffer);
}

void outStream_writeUInt(struct OutStream* outStream, uint_t i) {
    char buffer[21];  /* Max chars for 64-bit integer */
    sprintf(buffer, "%lu", i);
    outStream_writeString(outStream, buffer);
}

void outStream_writeReal(struct OutStream* outStream, real_t r) {
    char buffer[32];  /* Max chars for 64-bit double */
    sprintf(buffer, "%E", r);
    outStream_writeString(outStream, buffer);
}

/* Object functions ******************/

void outStream_show(struct OutStream* self, struct OutStream* outStream) {
    (void)self;
    outStream_writeString(outStream, "OutStream{");
    switch (self->streamType) {
        case OST_File:
            if (self->file == stdout) {
                outStream_writeString(outStream, "stdout");
            }
            else if (self->file == stderr) {
                outStream_writeString(outStream, "stdout");
            }
            else {
                outStream_writeInt(outStream, self->file->_fileno);
            }
            break;
        case OST_ByteBuffer:
            byteBuffer_show(self->byteBuffer, outStream);
            break;
        default:
            assert(false);
            break;
    }
    outStream_writeChar(outStream, '}');
}

/* Private functions *********************************************************/

void _outStream_fwriteList(struct OutStream* outStream, va_list args) {
    bool_t contin = true;
    while (contin) {
        int argType = va_arg(args, int);
        switch (argType) {
            case 'C': {
                    int c = va_arg(args, int);
                    outStream_writeChar(outStream, c);
                }
                break;
            case 'I': {
                    int_t i = va_arg(args, int_t);
                    outStream_writeInt(outStream, i);
                }
                break;
            case 'O': {
                    struct Object* obj = va_arg(args, struct Object*);
                    show(obj, outStream);
                }
                break;
            case 'S': {
                    string_t s = va_arg(args, string_t);
                    outStream_writeString(outStream, s);
                }
                break;
            case 0:
                contin = false;
                break;
            default:
                fprintf(stderr, "_outStream_fwriteList got unhandled argType '%c'\n", argType);
        }
    }
    va_end(args);
}

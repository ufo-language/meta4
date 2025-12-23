#include <stdarg.h>
#include <assert.h>
#include <inttypes.h>
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
    assert(outStream->streamType < 2);
    return outStream;
}

struct OutStream* outStream_new_byteBuffer(struct ByteBuffer* byteBuffer) {
    struct OutStream* outStream = (struct OutStream*)object_new(OT_OutStream, NWORDS(struct OutStream));
    outStream->streamType = OST_ByteBuffer;
    outStream->byteBuffer = byteBuffer;
    assert(outStream->streamType < 2);
    return outStream;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void outStream_nl(struct OutStream* outStream) {
    assert(outStream->streamType < 2);
    outStream_writeChar(outStream, '\n');
}

void outStream_fwrite(struct OutStream* outStream, ...) {
    assert(outStream->streamType < 2);
    va_list args;
    va_start(args, outStream);
    _outStream_fwriteList(outStream, args);
    va_end(args);
}

void outStream_fwriteLn(struct OutStream* outStream, ...) {
    assert(outStream->streamType < 2);
    va_list args;
    va_start(args, outStream);
    _outStream_fwriteList(outStream, args);
    va_end(args);
    outStream_nl(outStream);
}

void outStream_writeChar(struct OutStream* outStream, char c) {
    assert(outStream->streamType < 2);
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

void outStream_writeChars(struct OutStream* outStream, count_t nChars, const string_t chars) {
    assert(outStream->streamType < 2);
    switch (outStream->streamType) {
        case OST_File:
            assert(false);
            break;
        case OST_ByteBuffer: {
                byteBuffer_appendBytes(outStream->byteBuffer, nChars, (byte_t*)chars);
            }
            break;
        default:
            assert(false);
            break;
    }
}

#include "object/globals.h"
void outStream_writeString(struct OutStream* outStream, const string_t s) {
    assert(outStream->streamType < 2);
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
            fprintf(stderr, "outStream_writeString got unhandled stream type %d\n", outStream->streamType);
            assert(false);
            break;
    }
}

void outStream_writeInt(struct OutStream* outStream, int_t i) {
    assert(outStream->streamType < 2);
    char buffer[21];  /* Max chars for 64-bit integer */
    sprintf(buffer, "%ld", i);
    outStream_writeString(outStream, buffer);
}

void outStream_writeHexInt(struct OutStream* outStream, uint_t i) {
    assert(outStream->streamType < 2);
    enum {
        BufferSize = 17
    };
    char buffer[BufferSize];// = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  /* Max chars for 64-bit hexadecimal integer */
#if 0
/* Somewhere between the call to sprintf and the call to _itoa_word there is'
   an uninitialized variable. (but it might be in my code and just being propagated to sprintf)
    ==683732==    at 0x48D8052: _itoa_word (_itoa.c:184)
    ==683732==    by 0x48E2C9B: __printf_buffer (vfprintf-process-arg.c:155)
    ==683732==    by 0x49019E6: __vsprintf_internal (iovsprintf.c:62)
    ==683732==    by 0x48DF4C6: sprintf (sprintf.c:30)
*/
    sprintf(buffer, "%lX", i);
    outStream_writeString(outStream, buffer);
#else
    static string_t hexChars = "0123456789ABCDEF";
    char* ptr = &buffer[BufferSize - 1];
    *ptr = 0;
    if (i == 0) {  /* TODO i is uninitialized */
        *--ptr = '0';
    }
    else {
        while (i > 0) {
            byte_t digit = i % 16;
            // --ptr;
            *--ptr = hexChars[digit];
            i /= 16;
        }
    }
    outStream_writeString(outStream, ptr);
#endif
}

void outStream_writeUInt(struct OutStream* outStream, uint_t i) {
    assert(outStream->streamType < 2);
    char buffer[21];  /* Max chars for 64-bit integer */
    sprintf(buffer, "%lu", i);
    outStream_writeString(outStream, buffer);
}

void outStream_writeReal(struct OutStream* outStream, real_t r) {
    assert(outStream->streamType < 2);
    char buffer[32];  /* Max chars for 64-bit double */
    sprintf(buffer, "%E", r);
    outStream_writeString(outStream, buffer);
}

/* Object functions ******************/

void outStream_show(struct OutStream* self, struct OutStream* outStream) {
    (void)self;
    assert(outStream->streamType < 2);
    assert(self->streamType < 2);
    outStream_writeString(outStream, "OutStream{");
    switch (self->streamType) {
        case OST_File:
            if (self->file == stdout) {
                outStream_writeString(outStream, "stdout");
            }
            else if (self->file == stderr) {
                outStream_writeString(outStream, "stderr");
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
    assert(outStream->streamType < 2);
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

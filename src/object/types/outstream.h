#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum OutStreamType {
    OST_File, OST_ByteBuffer
};

struct ByteBuffer;

struct OutStream {
    struct Object obj;
    enum OutStreamType streamType;
    union {
        FILE* file;
        struct ByteBuffer* byteBuffer;
    };
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct OutStream* outStream_new_file(FILE* file);
struct OutStream* outStream_new_byteBuffer(struct ByteBuffer* byteBuffer);

/* Public functions **********************************************************/

/* Unique functions ******************/

void outStream_nl(struct OutStream* outStream);

void outStream_fwrite(struct OutStream* outStream, ...);
void outStream_fwriteLn(struct OutStream* outStream, ...);

void outStream_writeChar(struct OutStream* outStream, char c);
void outStream_writeString(struct OutStream* outStream, const string_t s);

void outStream_writeInt(struct OutStream* outStream, int_t i);
void outStream_writeHexInt(struct OutStream* outStream, uint_t i);
void outStream_writeUInt(struct OutStream* outStream, uint_t i);
void outStream_writeReal(struct OutStream* outStream, real_t i);

/* Object functions ******************/

void outStream_show(struct OutStream* self, struct OutStream* outStream);

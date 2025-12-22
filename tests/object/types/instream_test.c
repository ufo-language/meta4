#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/types/bytebuffer.h"
#include "object/types/instream.h"
#include "object/types/outstream.h"
#include "object/types/string.h"

#include "debug.h"
int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(inStream_checkConstruction)
        struct ByteBuffer* bb = byteBuffer_new();
        struct InStream* inStream = inStream_new_byteBuffer(bb);
        ASSERT_ISA(OT_InStream, inStream);
        ASSERT_IEQ(IST_ByteBuffer, inStream->streamType);
        EXPECT_EQ(bb, inStream->byteBuffer);
    END

    TEST(inStream_checkAvailable_byteBuffer)
        struct ByteBuffer* bb = byteBuffer_new();
        struct InStream* inStream = inStream_new_byteBuffer(bb);
        ASSERT_IEQ(0, inStream_available(inStream));
        byteBuffer_appendByte(bb, 0x20);
        ASSERT_IEQ(1, inStream_available(inStream));
        byteBuffer_appendByte(bb, 0x21);
        ASSERT_IEQ(2, inStream_available(inStream));
    END

    TEST(inStream_checkReadByte_byteBuffer)
        struct ByteBuffer* bb = byteBuffer_new();
        struct InStream* inStream = inStream_new_byteBuffer(bb);
        ASSERT_IEQ(0, inStream_available(inStream));
        count_t nBytes = 4;
        byte_t bytes[] = {0x20, 0x21};
        byteBuffer_appendBytes(bb, nBytes, bytes);
        ASSERT_IEQ(nBytes, inStream_available(inStream));
        byte_t byte;
        ASSERT_TRUE(inStream_readByte(inStream, &byte));
        ASSERT_IEQ(bytes[0], byte);
        ASSERT_TRUE(inStream_readByte(inStream, &byte));
        ASSERT_IEQ(bytes[1], byte);
    END

    TEST(inStream_checkReadString_byteBuffer)
        struct ByteBuffer* bb = byteBuffer_new();
        count_t nBytes = 3;
        byte_t bytes[] = {0x31, 0x32, 0x33};
        byteBuffer_appendBytes(bb, nBytes, bytes);
        struct InStream* inStream = inStream_new_byteBuffer(bb);
        struct String* string;
        ASSERT_TRUE(inStream_readString(inStream, &string));
        DEBUG1("inStream_checkReadString_byteBuffer got string ", string);
        ASSERT_IEQ(0, strcmp("123", string->chars));
    END

    TEST(inStream_checkFromOutStream)
        struct ByteBuffer* bb = byteBuffer_new();
        struct OutStream* os = outStream_new_byteBuffer(bb);
        outStream_fwriteLn(os,
            'S', "Nil = ",
            'O', g_nil,
            0);
        struct InStream* inStream = inStream_new_byteBuffer(bb);
        struct String* string;
        ASSERT_TRUE(inStream_readString(inStream, &string));
        DEBUG1("inStream_checkReadString_byteBuffer got string ", string);
        ASSERT_IEQ(0, strcmp("Nil = nil\n", string->chars));
    END

    END_TESTS
}

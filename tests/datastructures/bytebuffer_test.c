#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/count.h"
#include "object/types/bytebuffer.h"
#include "object/types/string.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(byteBuffer_checkConstruction)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        ASSERT_ISA(OT_ByteBuffer, byteBuffer);
        ASSERT_IEQ(NWORDS(struct ByteBuffer), byteBuffer->obj.nWords);
        ASSERT_IEQ(0, byteBuffer->nBytes);
        ASSERT_IEQ(0, byteBuffer->nResizes);
        ASSERT_IEQ(DEFAULT_BYTE_BUFFER_SIZE, byteBuffer->capacity);
    END

    TEST(byteBuffer_checkCount)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        count_t nElems;
        EXPECT_TRUE(count(OBJ(byteBuffer), &nElems));
        EXPECT_IEQ(0, nElems);
    END

    TEST(byteBuffer_checkAppendByte)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        EXPECT_IEQ(0, byteBuffer->nBytes);
        byteBuffer_appendByte(byteBuffer, 99);
        EXPECT_IEQ(1, byteBuffer->nBytes);
        EXPECT_IEQ(99, byteBuffer->bytes[0]);
        byteBuffer_appendByte(byteBuffer, 100);
        EXPECT_IEQ(2, byteBuffer->nBytes);
        EXPECT_IEQ(100, byteBuffer->bytes[1]);
        EXPECT_IEQ(0, byteBuffer->nResizes);
    END

    TEST(byteBuffer_checkAppendBytes)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        EXPECT_IEQ(0, byteBuffer->nBytes);
        byte_t bytes[] = {99, 100, 101};
        byteBuffer_appendBytes(byteBuffer, 3, bytes);
        EXPECT_IEQ(3, byteBuffer->nBytes);
        EXPECT_IEQ(99, byteBuffer->bytes[0]);
        EXPECT_IEQ(100, byteBuffer->bytes[1]);
        EXPECT_IEQ(101, byteBuffer->bytes[2]);
        EXPECT_IEQ(0, byteBuffer->nResizes);
    END

    TEST(byteBuffer_checkResize)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        EXPECT_IEQ(0, byteBuffer->nBytes);
        for (count_t n=0; n<DEFAULT_BYTE_BUFFER_SIZE; ++n) {
            byteBuffer_appendByte(byteBuffer, (byte_t)n + 100);
        }
        EXPECT_IEQ(DEFAULT_BYTE_BUFFER_SIZE, byteBuffer->nBytes);
        EXPECT_IEQ(0, byteBuffer->nResizes);
        count_t nBytes = byteBuffer->nBytes;
        byteBuffer_appendByte(byteBuffer, 99);
        EXPECT_IEQ(DEFAULT_BYTE_BUFFER_SIZE + 1, byteBuffer->nBytes);
        EXPECT_IEQ(1, byteBuffer->nResizes);
        EXPECT_IEQ(DEFAULT_BYTE_BUFFER_SIZE * 2, byteBuffer->capacity);
        EXPECT_IEQ(nBytes + 1, byteBuffer->nBytes);
    END

    TEST(byteBuffer_toString)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        byteBuffer_appendByte(byteBuffer, 'a');
        byteBuffer_appendByte(byteBuffer, 'b');
        byteBuffer_appendByte(byteBuffer, 'c');
        struct String* string = byteBuffer_toString(byteBuffer);
        ASSERT_ISA(OT_String, string);
        ASSERT_IEQ(3, string->nChars);
        ASSERT_IEQ(0, strcmp("abc", string->chars));
    END

    END_TESTS
}

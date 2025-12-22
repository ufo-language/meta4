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
        ASSERT_IEQ(0, byteBuffer_count(byteBuffer));
        ASSERT_IEQ(0, byteBuffer->nResizes);
        ASSERT_IEQ(ByteBuffer_DefaultCapacity, byteBuffer->capacity);
    END

    TEST(byteBuffer_checkCount)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        count_t nElems;
        EXPECT_TRUE(count(OBJ(byteBuffer), &nElems));
        EXPECT_IEQ(0, nElems);
    END

    TEST(byteBuffer_checkAppendByte)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        EXPECT_IEQ(0, byteBuffer_count(byteBuffer));
        byteBuffer_appendByte(byteBuffer, 99);
        EXPECT_IEQ(1, byteBuffer_count(byteBuffer));
        EXPECT_IEQ(99, byteBuffer->bytes[0]);
        byteBuffer_appendByte(byteBuffer, 100);
        EXPECT_IEQ(2, byteBuffer_count(byteBuffer));
        EXPECT_IEQ(100, byteBuffer->bytes[1]);
        EXPECT_IEQ(0, byteBuffer->nResizes);
    END

    TEST(byteBuffer_checkAppendBytes)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        EXPECT_IEQ(0, byteBuffer_count(byteBuffer));
        byte_t bytes[] = {99, 100, 101};
        byteBuffer_appendBytes(byteBuffer, 3, bytes);
        EXPECT_IEQ(3, byteBuffer_count(byteBuffer));
        EXPECT_IEQ(99, byteBuffer->bytes[0]);
        EXPECT_IEQ(100, byteBuffer->bytes[1]);
        EXPECT_IEQ(101, byteBuffer->bytes[2]);
        EXPECT_IEQ(0, byteBuffer->nResizes);
    END

    TEST(byteBuffer_checkResize)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        EXPECT_IEQ(0, byteBuffer_count(byteBuffer));
        for (count_t n=0; n<ByteBuffer_DefaultCapacity; ++n) {
            byteBuffer_appendByte(byteBuffer, (byte_t)n + 100);
        }
        EXPECT_IEQ(ByteBuffer_DefaultCapacity, byteBuffer_count(byteBuffer));
        EXPECT_IEQ(0, byteBuffer->nResizes);
        count_t nBytes = byteBuffer_count(byteBuffer);
        byteBuffer_appendByte(byteBuffer, 99);
        EXPECT_IEQ(ByteBuffer_DefaultCapacity + 1, byteBuffer_count(byteBuffer));
        EXPECT_IEQ(1, byteBuffer->nResizes);
        EXPECT_IEQ(ByteBuffer_DefaultCapacity * 2, byteBuffer->capacity);
        EXPECT_IEQ(nBytes + 1, byteBuffer_count(byteBuffer));
    END

    TEST(byteBuffer_checkReadString)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        byteBuffer_appendByte(byteBuffer, 'a');
        byteBuffer_appendByte(byteBuffer, 'b');
        byteBuffer_appendByte(byteBuffer, 'c');
        struct String* string;
        ASSERT_TRUE(byteBuffer_readString(byteBuffer, &string));
        ASSERT_ISA(OT_String, string);
        ASSERT_IEQ(3, string->nChars);
        ASSERT_IEQ(0, strcmp("abc", string->chars));
    END

    TEST(byteBuffer_checkShow)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        byteBuffer_appendByte(byteBuffer, '0');
        byteBuffer_appendByte(byteBuffer, '1');
        byteBuffer_appendByte(byteBuffer, '2');
        SHOW("Should show 'ByteBuffer{30:31:32}'", byteBuffer);
    END

    TEST(byteBuffer_checkRead)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        byteBuffer_appendByte(byteBuffer, '0');
        byteBuffer_appendByte(byteBuffer, '1');
        byteBuffer_appendByte(byteBuffer, '2');
        ASSERT_IEQ(3, byteBuffer_count(byteBuffer));
        byte_t byte;
        ASSERT_TRUE(byteBuffer_readByte(byteBuffer, &byte));
        ASSERT_IEQ('0', byte);
        ASSERT_IEQ(2, byteBuffer_count(byteBuffer));
        ASSERT_TRUE(byteBuffer_readByte(byteBuffer, &byte));
        ASSERT_IEQ('1', byte);
        ASSERT_IEQ(1, byteBuffer_count(byteBuffer));
        ASSERT_TRUE(byteBuffer_readByte(byteBuffer, &byte));
        ASSERT_IEQ('2', byte);
        ASSERT_IEQ(0, byteBuffer_count(byteBuffer));
        ASSERT_FALSE(byteBuffer_readByte(byteBuffer, &byte));
    END

    TEST(byteBuffer_checkWriteThenRead_shouldResetIndexes)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        for (count_t n=0; n<ByteBuffer_DefaultCapacity; ++n) {
            byteBuffer_appendByte(byteBuffer, 0x20);
        }
        ASSERT_IEQ(ByteBuffer_DefaultCapacity, byteBuffer->nBytes);
        ASSERT_IEQ(ByteBuffer_DefaultCapacity, byteBuffer->writeIndex);
        ASSERT_IEQ(0, byteBuffer->nResizes);
        byte_t byte;
        for (count_t n=0; n<ByteBuffer_DefaultCapacity; ++n) {
            ASSERT_TRUE(byteBuffer_readByte(byteBuffer, &byte));
        }
        EXPECT_IEQ(0, byteBuffer->writeIndex);
        EXPECT_IEQ(0, byteBuffer->readIndex);
        EXPECT_IEQ(0, byteBuffer->nBytes);
    END

    TEST(byteBuffer_checkWriteThenRead_shouldCopyWithoutResizing)
        struct ByteBuffer* byteBuffer = byteBuffer_new();
        for (count_t n=0; n<ByteBuffer_DefaultCapacity; ++n) {
            byteBuffer_appendByte(byteBuffer, 0x20);
        }
        ASSERT_IEQ(ByteBuffer_DefaultCapacity, byteBuffer->nBytes);
        ASSERT_IEQ(ByteBuffer_DefaultCapacity, byteBuffer->writeIndex);
        ASSERT_IEQ(0, byteBuffer->nResizes);
        byte_t byte;
        for (count_t n=0; n<(ByteBuffer_DefaultCapacity / 2); ++n) {
            ASSERT_TRUE(byteBuffer_readByte(byteBuffer, &byte));
        }
        count_t nExpectedBytes = ByteBuffer_DefaultCapacity / 2;
        ASSERT_IEQ(nExpectedBytes, byteBuffer->nBytes);
        /* This write should force a "move" without resizing */
        byteBuffer_appendByte(byteBuffer, 0x21);
        ASSERT_IEQ(0, byteBuffer->nResizes);
        ASSERT_IEQ(nExpectedBytes + 1, byteBuffer->nBytes);
        EXPECT_IEQ(nExpectedBytes + 1, byteBuffer->writeIndex);
        EXPECT_IEQ(0, byteBuffer->readIndex);
    END

    END_TESTS
}

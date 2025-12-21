#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/bytebuffer.h"
#include "object/types/outstream.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(outStream_checkByteBuffer)
        struct ByteBuffer* bb = byteBuffer_new();
        struct OutStream* os = outStream_new_byteBuffer(bb);
        show((struct Object*)g_nil, os);
        EXPECT_IEQ(0, strncmp("nil", (char*)bb->bytes, 3));
    END

    END_TESTS
}

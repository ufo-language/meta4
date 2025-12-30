#include "_test.h"
#include "_typedefs.h"

#include "object/functions/hash.h"
#include "object/globals.h"
#include "object/types/boolean.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(boolean_checkConstruction)
        struct Boolean* boolean = boolean_new(true);
        ASSERT_ISA(OT_Boolean, boolean);
        EXPECT_TRUE(boolean->b);
        EXPECT_IEQ(NWORDS(struct Object) + 1, boolean->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Boolean), boolean->obj.nWords);
    END

    TEST(boolean_checkHash)
        word_t trueHash;
        ASSERT_TRUE(hash((struct Object*)g_true, &trueHash));
        word_t falseHash;
        ASSERT_TRUE(hash((struct Object*)g_false, &falseHash));
        EXPECT_INE(trueHash, falseHash);
    END

    END_TESTS
}

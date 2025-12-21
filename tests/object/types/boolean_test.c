#include "_test.h"
#include "_typedefs.h"

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

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/functions/compare.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(compare_checkIntInt)
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        EXPECT_IEQ(CompareEqual, compare(OBJ(i100), OBJ(i100)));
        EXPECT_IEQ(CompareLess, compare(OBJ(i100), OBJ(i200)));
        EXPECT_IEQ(CompareGreater, compare(OBJ(i200), OBJ(i100)));
    END

    END_TESTS
}

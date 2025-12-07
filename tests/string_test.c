#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/types/string.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(string_checkConstruction)
        struct String* abc = string_new("abc");
        ASSERT_ISA(OT_String, abc);
        ASSERT_IEQ(3, abc->nChars);
        ASSERT_IEQ(0, strcmp("abc", abc->chars));
    END

    TEST(string_checkEqual)
        struct String* abc1 = string_new("abc");
        struct String* abc2 = string_new("abc");
        struct String* def = string_new("def");
        EXPECT_TRUE(string_equal(abc1, abc2));
        EXPECT_FALSE(string_equal(abc1, def));
    END

    END_TESTS
}

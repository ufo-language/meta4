#include "_test.h"
#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/types/integer.h"
#include "object/types/term.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(errorTerm_check)
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        struct Term* et = errorTerm("Abc", "message",
            2,
            "Def", i100,
            "Ghi", i200);
        ASSERT_ISA(OT_Term, et);
        EXPECT_SHOW("Abc{\"message\", Def=100, Ghi=200}", et);
    END

    END_TESTS
}

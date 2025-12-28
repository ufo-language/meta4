#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(typeId_checkNames)
        const string_t unknown = "UNKNOWN";
        for (int n=0; n<OT_Max; ++n) {
            string_t name = typeName(n);
            ASSERT_PTRNE(0, name);
            SHOW("Type name", string_new(name));
            /* Do some sanity checking on the strings */
            EXPECT_TRUE(strlen(name) < 16);
            EXPECT_INE(0, strcmp(name, unknown));
            EXPECT_TRUE(name[0] >= 'A' && name[0] <= 'Z');
        }
    END

    END_TESTS
}

#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(typeId_checkNames)
        for (int n=0; n<OT_Max; ++n) {
            string_t name = typeName(n);
            // fprintf(stderr, "Type name %d = '%s'\n", n, name);
            ASSERT_PTRNE(0, name);
            /* Do some sanity checking on the strings */
            ASSERT_TRUE(strlen(name) < 16);
            ASSERT_TRUE(name[0] >= 'A' && name[0] <= 'Z');
        }
    END

    END_TESTS
}

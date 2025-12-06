#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/types/evaluator.h"
#include "object/types/identifier.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a1 = identifier_new("a");
    struct Identifier* a2 = identifier_new("a");
    struct Identifier* b = identifier_new("b");

    TEST(identifier_checkConstruction)
        ASSERT_IEQ(OT_Identifier, a1->obj.typeId);
        ASSERT_IEQ(0, strcmp("a", a1->name));
        ASSERT_IEQ(a1->hashCode, a2->hashCode);
        ASSERT_INE(a1->hashCode, b->hashCode);
    END

    TEST(identifier_checkEval)
        FORCE_FAIL()
    END

    END_TESTS
}

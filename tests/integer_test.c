#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/types/evaluator.h"
#include "object/types/integer.h"
#include "object/globals.h"
#include "object/functions/show.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(integer_checkConstruction)
        struct Integer* integer = integer_new(123);
        ASSERT_PTRNE(NULL, integer);
        ASSERT_IEQ(OT_Integer, integer->obj.typeId);
        EXPECT_IEQ(0, strcmp("Integer", typeName(integer->obj.typeId)));
    END

    TEST(integer_checkEval)
        struct Integer* integer = integer_new(123);
        struct Evaluator* etor = etor_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(integer), etor, &value))
        EXPECT_EQ(integer, value);
    END

    TEST(integer_checkShow)
        struct Integer* integer = integer_new(123);
        SHOW("Should show '123'", integer);
    END

    END_TESTS
}

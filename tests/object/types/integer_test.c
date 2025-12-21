#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/equal.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(integer_checkConstruction)
        struct Integer* integer = integer_new(123);
        ASSERT_PTRNE(NULL, integer);
        ASSERT_ISA(OT_Integer, integer);
        EXPECT_IEQ(0, strcmp("Integer", typeName(integer->obj.typeId)));
        EXPECT_IEQ(NWORDS(struct Object) + 1, integer->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Integer), integer->obj.nWords);
    END

    TEST(integer_checkEqual)
        struct Integer* i100a = integer_new(100);
        struct Integer* i100b = integer_new(100);
        struct Integer* i200 = integer_new(200);
        EXPECT_TRUE(equal(OBJ(i100a), OBJ(i100b)));
        EXPECT_FALSE(equal(OBJ(i100a), OBJ(i200)));
    END

    TEST(integer_checkEval)
        struct Integer* integer = integer_new(123);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(integer), etor, &value))
        EXPECT_EQ(integer, value);
    END

    TEST(integer_checkShow)
        struct Integer* integer = integer_new(123);
        SHOW("Should show '123'", integer);
    END

    END_TESTS
}

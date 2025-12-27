#include "_test.h"
#include "_typedefs.h"

#include "object/globals.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/array.h"
#include "object/types/integer.h"
#include "object/types/subscript.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(subscript_checkConstruction)
        struct Subscript* subs = subscript_new(OBJ(g_nil), OBJ(g_nil));
        ASSERT_ISA(OT_Subscript, subs);
        ASSERT_IEQ(NWORDS(struct Object) + 2, subs->obj.nWords);
        ASSERT_IEQ(NWORDS(struct Subscript), subs->obj.nWords);
    END

    TEST(subscript_checkAssign)
        struct Integer* i0 = integer_new(0);
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        struct Array* array = array_new_withElem(1, OBJ(i100));
        struct Subscript* subs = subscript_new(OBJ(array), OBJ(i0));
        struct Object* error;
        ASSERT_TRUE(subscript_assign(subs, OBJ(i200), &error));
        EXPECT_EQ(i200, array->elems[0]);
    END

    END_TESTS
}

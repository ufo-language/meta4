#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/types/evaluator.h"
#include "object/types/nil.h"
#include "object/globals.h"
#include "object/functions/show.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(nil_checkConstruction)
        struct Nil* nil = nil_new();
        ASSERT_PTRNE(NULL, nil);
        ASSERT_IEQ(OT_Nil, nil->obj.typeId);
        EXPECT_IEQ(0, strcmp("Nil", typeName(nil->obj.typeId)));
    END

    TEST(nil_checkEval)
        struct Nil* nil = nil_new();
        struct Evaluator* etor = evaluator_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(nil), etor, &value))
        EXPECT_EQ(nil, value);
    END

    TEST(nil_checkShow)
        SHOW("Should show 'nil'", g_nil);
    END

    END_TESTS
}

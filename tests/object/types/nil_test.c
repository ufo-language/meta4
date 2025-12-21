#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/types/nil.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(nil_checkConstruction)
        struct Nil* nil = nil_new();
        ASSERT_PTRNE(NULL, nil);
        ASSERT_ISA(OT_Nil, nil);
        EXPECT_IEQ(0, strcmp("Nil", typeName(nil->obj.typeId)));
        EXPECT_IEQ(NWORDS(struct Object), nil->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Nil), nil->obj.nWords);
    END

    TEST(nil_checkEval)
        struct Nil* nil = nil_new();
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(nil), etor, &value))
        EXPECT_EQ(nil, value);
    END

    TEST(nil_checkShow)
        SHOW("Should show 'nil'", g_nil);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/types/evaluator.h"
#include "object/types/nil.h"
#include "object/globals.h"

static void _checkEval(struct Evaluator* etor) {
}

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(nil_checkConstruction)
        struct Nil* nil = nil_new();
        ASSERT_PTRNE(NULL, nil);
        ASSERT_IEQ(OT_Nil, nil->obj.typeId);
    END

    TEST(nil_checkEval)
        struct Evaluator* etor = etor_new();
        etor_run(etor, _checkEval);
        etor_show(etor, stderr);
    END

    TEST(nil_checkShow)
        MESSAGE("Should show 'nil':");
        nil_show(g_nil, stderr);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/nil.h"

// static void _checkConstruction(struct Evaluator* etor) {
// }

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(globals_checkInit)
        ASSERT_PTRNE(NULL, g_nil);
        ASSERT_IEQ(OT_Nil, g_nil->obj.typeId);
    END

    END_TESTS
}

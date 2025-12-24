#include "_test.h"
#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/subscript.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(subscript_checkConstruction)
        struct Subscript* subs = subscript_new(OBJ(g_nil), OBJ(g_nil));
        ASSERT_ISA(OT_Subscript, subs);
        ASSERT_IEQ(NWORDS(struct Object) + 2, subs->obj.nWords);
        ASSERT_IEQ(NWORDS(struct Subscript), subs->obj.nWords);
    END

    END_TESTS
}

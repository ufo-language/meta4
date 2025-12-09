#include "_test.h"
#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/nil.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(globals_checkInit)
        ASSERT_PTRNE(NULL, g_nil);
        ASSERT_ISA(OT_Nil, g_nil);
        ASSERT_ISA(OT_Null, g_uniqueObject);
    END

    TEST(globale_checkShowUniqueObject)
        SHOW("Should show 'Null/Unique'", g_uniqueObject);
    END

    END_TESTS
}

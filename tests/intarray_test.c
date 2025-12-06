#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/typeids.h"
#include "object/types/intarray.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    int_t elems[] = {100, 200, 300};

    TEST(intArray_checkConstruction)
        struct IntArray* intArray = intArray_new_noFill(3);
        ASSERT_IEQ(OT_IntArray, intArray->obj.typeId);
        EXPECT_IEQ(3, intArray->nElems);
        EXPECT_IEQ(0, strcmp("IntArray", typeName(intArray->obj.typeId)));
    END

    TEST(intArray_checkConstruction_withElem)
        struct IntArray* intArray = intArray_new_elem(3, 100);
        ASSERT_IEQ(3, intArray->nElems);
        EXPECT_IEQ(100, intArray->elems[0]);
        EXPECT_IEQ(100, intArray->elems[1]);
        EXPECT_IEQ(100, intArray->elems[2]);
    END

    TEST(intArray_checkConstruction_withElems)
        struct IntArray* intArray = intArray_new_elems(3, elems);
        ASSERT_IEQ(3, intArray->nElems);
        EXPECT_IEQ(100, intArray->elems[0]);
        EXPECT_IEQ(200, intArray->elems[1]);
        EXPECT_IEQ(300, intArray->elems[2]);
    END

    TEST(intArray_checkShow)
        struct IntArray* intArray = intArray_new_elems(3, elems);
        SHOW("Should show 'IntArray{100, 200, 300}'", intArray);
    END

    END_TESTS
}

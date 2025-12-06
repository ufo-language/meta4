#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/intarray.h"
#include "object/functions/show.h"

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

#if 0
    TEST(intArray_checkEval)
        struct IntArray* intArray = intArray_new_elems(3, elems);
        struct Evaluator* etor = evaluator_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(intArray), etor, &value))
        ASSERT_PTRNE(intArray, value);
        ASSERT_IEQ(OT_Array, value->typeId);
        struct IntArray* intArrayValue = (struct IntArray*)value;
        ASSERT_IEQ(3, intArrayValue->nElems);
        EXPECT_EQ(i100, intArray->elems[0]);
        EXPECT_EQ(i200, intArray->elems[1]);
        EXPECT_EQ(i300, intArray->elems[2]);
    END
#endif

    TEST(intArray_checkShow)
        struct IntArray* intArray = intArray_new_elems(3, elems);
        SHOW("Should show 'IntArray{100, 200, 300}'", intArray);
    END

    END_TESTS
}

#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/evaluator.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i0 = integer_new(0);
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);
    struct Integer* i300 = integer_new(300);
    struct Object* elems[] = {OBJ(i100), OBJ(i200), OBJ(i300)};

    TEST(array_checkConstruction)
        struct Array* array = array_new_noFill(3);
        ASSERT_IEQ(OT_Array, array->obj.typeId);
        EXPECT_IEQ(3, array->nElems);
        EXPECT_IEQ(0, strcmp("Array", typeName(array->obj.typeId)));
    END

    TEST(array_checkConstruction_withElem)
        struct Array* array = array_new_elem(3, OBJ(i100));
        ASSERT_IEQ(3, array->nElems);
        EXPECT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i100, array->elems[1]);
        EXPECT_EQ(i100, array->elems[2]);
    END

    TEST(array_checkConstruction_withElems)
        struct Array* array = array_new_elems(3, elems);
        ASSERT_IEQ(3, array->nElems);
        EXPECT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i200, array->elems[1]);
        EXPECT_EQ(i300, array->elems[2]);
    END

    TEST(array_checkSetAndGet)
        struct Array* array = array_new_elem(3, OBJ(i0));
        ASSERT_EQ(i0, array_get_unsafe(array, 0));
        ASSERT_EQ(i0, array_get_unsafe(array, 1));
        ASSERT_EQ(i0, array_get_unsafe(array, 2));
        array_set_unsafe(array, 0, OBJ(i100));
        ASSERT_EQ(i100, array_get_unsafe(array, 0));
        EXPECT_EQ(i0, array_get_unsafe(array, 1));
        EXPECT_EQ(i0, array_get_unsafe(array, 2));
        array_set_unsafe(array, 1, OBJ(i200));
        EXPECT_EQ(i100, array_get_unsafe(array, 0));
        ASSERT_EQ(i200, array_get_unsafe(array, 1));
        EXPECT_EQ(i0, array_get_unsafe(array, 2));
        array_set_unsafe(array, 2, OBJ(i300));
        EXPECT_EQ(i100, array_get_unsafe(array, 0));
        EXPECT_EQ(i200, array_get_unsafe(array, 1));
        ASSERT_EQ(i300, array_get_unsafe(array, 2));
    END

    TEST(array_checkEval)
        struct Array* array = array_new_elems(3, elems);
        struct Evaluator* etor = evaluator_new();
        struct Object* value;
        ASSERT_TRUE(eval(OBJ(array), etor, &value))
        ASSERT_PTRNE(array, value);
        ASSERT_IEQ(OT_Array, value->typeId);
        struct Array* arrayValue = (struct Array*)value;
        ASSERT_IEQ(3, arrayValue->nElems);
        EXPECT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i200, array->elems[1]);
        EXPECT_EQ(i300, array->elems[2]);
    END

    TEST(array_checkShow)
        struct Array* array = array_new_elems(3, elems);
        SHOW("Should show '{100, 200, 300}'", array);
    END

    END_TESTS
}

#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/compare.h"
#include "object/functions/match.h"
#include "object/globals.h"
#include "object/typeids.h"
#include "object/types/array.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a = identifier_new("a");
    struct Identifier* b = identifier_new("b");
    struct Identifier* c = identifier_new("c");
    struct Integer* i0 = integer_new(0);
    struct Integer* i1 = integer_new(1);
    struct Integer* i2 = integer_new(2);
    struct Integer* i3 = integer_new(3);
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);
    struct Integer* i300 = integer_new(300);
    struct Object* elems[] = {OBJ(i100), OBJ(i200), OBJ(i300)};

    TEST(array_checkConstruction)
        count_t nElems = 3;
        struct Array* array = array_new_noFill(nElems);
        ASSERT_ISA(OT_Array, array);
        EXPECT_IEQ(nElems, array->nElems);
        EXPECT_IEQ(NWORDS(struct Object) + 1 + nElems, array->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Array) + nElems, array->obj.nWords);
        EXPECT_IEQ(0, strcmp("Array", typeName(array->obj.typeId)));
    END

    TEST(array_checkConstruction_withElem)
        struct Array* array = array_new_withElem(3, OBJ(i100));
        ASSERT_IEQ(3, array->nElems);
        EXPECT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i100, array->elems[1]);
        EXPECT_EQ(i100, array->elems[2]);
    END

    TEST(array_checkConstruction_withElems)
        struct Array* array = array_new_withElems(3, elems);
        ASSERT_IEQ(3, array->nElems);
        EXPECT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i200, array->elems[1]);
        EXPECT_EQ(i300, array->elems[2]);
    END

    TEST(array_checkSetAndGet)
        struct Array* array = array_new_withElem(3, OBJ(i0));
        ASSERT_EQ(i0, array->elems[0]);
        ASSERT_EQ(i0, array->elems[1]);
        ASSERT_EQ(i0, array->elems[2]);
        array->elems[0] = OBJ(i100);
        ASSERT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i0, array->elems[1]);
        EXPECT_EQ(i0, array->elems[2]);
        array->elems[1] = OBJ(i200);
        EXPECT_EQ(i100, array->elems[0]);
        ASSERT_EQ(i200, array->elems[1]);
        EXPECT_EQ(i0, array->elems[2]);
        array->elems[2] = OBJ(i300);
        EXPECT_EQ(i100, array->elems[0]);
        EXPECT_EQ(i200, array->elems[1]);
        ASSERT_EQ(i300, array->elems[2]);
    END

    TEST(array_checkEvalElems_rec)
        count_t nElems = 3;
        struct Object* elems[] = {OBJ(a), OBJ(b), OBJ(c)};
        struct Object* newElems[] = {g_uniqueObject, g_uniqueObject, g_uniqueObject};
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        etor_rec_bind(etor, c, OBJ(i300));
        struct Object* error = g_uniqueObject;
        ASSERT_TRUE(array_eval_rec_usingElems(nElems, elems, newElems, etor, &error));
        EXPECT_EQ(i100, newElems[0]);
        EXPECT_EQ(i200, newElems[1]);
        EXPECT_EQ(i300, newElems[2]);
    END

    TEST(array_checkEval)
        struct Object* identElems[] = {OBJ(a), OBJ(b), OBJ(c)};
        struct Array* array = array_new_withElems(3, identElems);
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        etor_rec_bind(etor, c, OBJ(i300));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(array), etor, &value))
        ASSERT_PTRNE(array, value);
        ASSERT_ISA(OT_Array, value);
        struct Array* arrayValue = (struct Array*)value;
        ASSERT_IEQ(3, arrayValue->nElems);
        EXPECT_EQ(i100, arrayValue->elems[0]);
        EXPECT_EQ(i200, arrayValue->elems[1]);
        EXPECT_EQ(i300, arrayValue->elems[2]);
    END

    TEST(check_compare_equal)
        struct Object* elems[] = {OBJ(i100), OBJ(i200), OBJ(i300)};
        struct Array* array1 = array_new_withElems(3, elems);
        struct Array* array2 = array_new_withElems(3, elems);
        ASSERT_IEQ(CompareEqual, compare(OBJ(array1), OBJ(array2)));
    END

    TEST(array_checkMatch)
        struct Object* identElems[] = {OBJ(a), OBJ(b), OBJ(c)};
        struct Array* array = array_new_withElems(3, identElems);
        struct Object* intElems[] = {OBJ(i100), OBJ(i200), OBJ(i300)};
        struct Array* otherArray = array_new_withElems(3, intElems);
        struct Vector* bindings = vector_new();
        ASSERT_TRUE(match(OBJ(array), OBJ(otherArray), bindings));
        struct Object* value;
        ASSERT_TRUE(vector_lookup(bindings, OBJ(a), &value));
        EXPECT_EQ(i100, value);
        ASSERT_TRUE(vector_lookup(bindings, OBJ(b), &value));
        EXPECT_EQ(i200, value);
        ASSERT_TRUE(vector_lookup(bindings, OBJ(c), &value));
        EXPECT_EQ(i300, value);
    END

    TEST(array_checkSafeGet)
        struct Array* array = array_new_withElems(3, elems);
        struct Object* elem;
        /* array_get */
        ASSERT_TRUE(array_get(array, OBJ(i0), &elem));
        EXPECT_EQ(i100, elem);
        ASSERT_TRUE(array_get(array, OBJ(i1), &elem));
        EXPECT_EQ(i200, elem);
        ASSERT_TRUE(array_get(array, OBJ(i2), &elem));
        EXPECT_EQ(i300, elem);
        ASSERT_FALSE(array_get(array, OBJ(i3), &elem));
        EXPECT_ISA(OT_Term, elem);
        /* array_get_index_t */
        ASSERT_TRUE(array_get_index_t(array, 0, &elem));
        EXPECT_EQ(i100, elem);
        ASSERT_TRUE(array_get_index_t(array, 1, &elem));
        EXPECT_EQ(i200, elem);
        ASSERT_TRUE(array_get_index_t(array, 2, &elem));
        EXPECT_EQ(i300, elem);
        ASSERT_FALSE(array_get_index_t(array, 3, &elem));
        EXPECT_ISA(OT_Term, elem);
    END

    TEST(array_checkLookup)
        count_t nElems = 6;
        struct Object* elems[] = {OBJ(a), OBJ(i100), OBJ(b), OBJ(i200), OBJ(c), OBJ(i300)};
        struct Array* array = array_new_withElems(nElems, elems);
        struct Object* value;
        ASSERT_TRUE(array_lookup_usingElems(nElems, array->elems, OBJ(a), &value));
        EXPECT_EQ(i100, value);
        ASSERT_TRUE(array_lookup_usingElems(nElems, array->elems, OBJ(b), &value));
        EXPECT_EQ(i200, value);
        ASSERT_TRUE(array_lookup_usingElems(nElems, array->elems, OBJ(c), &value));
        EXPECT_EQ(i300, value);
        struct Identifier* d = identifier_new("d");
        ASSERT_FALSE(array_lookup_usingElems(nElems, array->elems, OBJ(d), &value));
    END
    
    TEST(array_checkLocate)
        count_t nElems = 6;
        struct Object* elems[] = {OBJ(a), OBJ(i100), OBJ(b), OBJ(i200), OBJ(c), OBJ(i300)};
        struct Array* array = array_new_withElems(nElems, elems);
        int_t index;
        ASSERT_TRUE(array_locate_usingElems(nElems, array->elems, OBJ(a), &index));
        EXPECT_IEQ(1, index);
        ASSERT_TRUE(array_locate_usingElems(nElems, array->elems, OBJ(b), &index));
        EXPECT_IEQ(3, index);
        ASSERT_TRUE(array_locate_usingElems(nElems, array->elems, OBJ(c), &index));
        EXPECT_IEQ(5, index);
        struct Identifier* d = identifier_new("d");
        ASSERT_FALSE(array_locate_usingElems(nElems, array->elems, OBJ(d), &index));
    END

    TEST(array_checkShow)
        struct Array* array = array_new_withElems(3, elems);
        EXPECT_SHOW("{100, 200, 300}", array);
    END

    END_TESTS
}

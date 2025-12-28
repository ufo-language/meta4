#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/compare.h"
#include "object/functions/show.h"
#include "object/types/intvar.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(intVar_checkConstruction)
        struct IntVar* intVar = intVar_new(123);
        ASSERT_PTRNE(NULL, intVar);
        ASSERT_ISA(OT_IntVar, intVar);
        EXPECT_IEQ(0, strcmp("IntVar", typeName(intVar->obj.typeId)));
    END

    TEST(intVar_checkCompare)
        struct IntVar* i100a = intVar_new(100);
        struct IntVar* i100b = intVar_new(100);
        struct IntVar* i200 = intVar_new(200);
        EXPECT_IEQ(CompareEqual, compare(OBJ(i100a), OBJ(i100b)));
        EXPECT_INE(CompareEqual, compare(OBJ(i100a), OBJ(i200)));
        EXPECT_IEQ(CompareLess, compare(OBJ(i100a), OBJ(i200)));
        EXPECT_IEQ(CompareGreater, compare(OBJ(i200), OBJ(i100a)));
    END

    TEST(intVar_checkShow)
        struct IntVar* intVar = intVar_new(123);
        EXPECT_SHOW("IntVar{123}", intVar);
    END

    END_TESTS
}

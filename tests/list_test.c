#include "_test.h"
#include "_typedefs.h"

#include "object/functions/eval_rec.h"
#include "object/evaluator/etor_rec.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/list.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Symbolic* a = identifier_new("a");
    struct Symbolic* b = identifier_new("b");
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(list_checkConstruction)
        struct List* list = list_new(OBJ(i100), OBJ(i200));
        EXPECT_ISA(OT_List, list);
        ASSERT_EQ(i100, list->first);
        ASSERT_EQ(i200, list->rest);
    END

    TEST(list_checkEval)
        struct Etor_Rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        struct List* list = list_new(OBJ(a), OBJ(b));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(list), etor, &value));
        ASSERT_ISA(OT_List, value);
        EXPECT_EQ(i100, ((struct List*)value)->first);
        EXPECT_EQ(i200, ((struct List*)value)->rest);
    END

    END_TESTS
}

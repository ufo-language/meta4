#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/evaluator_recursive.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a1 = identifier_new("a");
    struct Identifier* a2 = identifier_new("a");
    struct Identifier* b = identifier_new("b");

    TEST(identifier_checkConstruction)
        ASSERT_IEQ(OT_Identifier, a1->obj.typeId);
        ASSERT_IEQ(0, strcmp("a", a1->name));
        ASSERT_IEQ(a1->hashCode, a2->hashCode);
        ASSERT_INE(a1->hashCode, b->hashCode);
    END

    TEST(identifier_checkEval)
        struct Integer* i100 = integer_new(100);
        struct Evaluator* etor = evaluator_new();
        evaluator_bind(etor, a1, OBJ(i100));
        struct Object* value;
        /* Verify that the binding is correct */
        ASSERT_TRUE(evaluator_lookup(etor, a1, &value));
        EXPECT_EQ(i100, value);
        /* Now check the eval function */
        ASSERT_TRUE(identifier_eval_recursive(a1, etor, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(identifier_checkClose_bound)
        struct Integer* i100 = integer_new(100);
        struct Evaluator* etor = evaluator_new();
        evaluator_bind(etor, a1, OBJ(i100));
        etor->operationType = Etor_Closing;
        struct Object* value;
        ASSERT_TRUE(identifier_eval_recursive(a1, etor, &value));
        ASSERT_EQ(i100, value);
    END

    TEST(identifier_checkClose_unbound)
        struct Evaluator* etor = evaluator_new();
        etor->operationType = Etor_Closing;
        struct Object* value;
        ASSERT_TRUE(identifier_eval_recursive(a1, etor, &value));
        ASSERT_EQ(a1, value);
    END

    END_TESTS
}

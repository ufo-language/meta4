#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_recursive.h"
#include "object/types/integer.h"
#include "object/types/symbol.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Symbolic* a1 = symbol_new("A");
    struct Symbolic* a2 = symbol_new("A");
    struct Symbolic* b = symbol_new("B");

    TEST(symbol_checkConstruction)
        ASSERT_IEQ(OT_Symbol, a1->obj.typeId);
        ASSERT_IEQ(0, strcmp("A", a1->name));
        ASSERT_IEQ(a1->hashCode, a2->hashCode);
        ASSERT_INE(a1->hashCode, b->hashCode);
    END

    TEST(symbol_checkEval)
        struct Evaluator* etor = etor_rec_new();
        struct Object* value;
        /* Now check the eval function */
        ASSERT_TRUE(eval_recursive(OBJ(a1), etor, &value));
        EXPECT_EQ(a1, value);
    END

    END_TESTS
}

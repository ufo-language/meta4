#include <string.h>

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/globals.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* a1 = identifier_new("a");
    struct Identifier* a2 = identifier_new("a");
    struct Identifier* b = identifier_new("b");
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(identifier_checkConstruction)
        ASSERT_ISA(OT_Identifier, a1);
        ASSERT_IEQ(0, strcmp("a", a1->name));
        count_t nChars = strlen("a") + 1;
        ASSERT_IEQ(a1->hashCode, a2->hashCode);
        ASSERT_INE(a1->hashCode, b->hashCode);
        EXPECT_IEQ(NWORDS(struct Object) + 1 + NBYTES_TO_WORDS(nChars), a1->obj.nWords);
        EXPECT_IEQ(NWORDS(struct Identifier) + NBYTES_TO_WORDS(nChars), a1->obj.nWords);
        EXPECT_EQ(a1, a2);
        EXPECT_NE(a1, b);
    END

    TEST(identifier_checkEval)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a1, OBJ(i100));
        struct Object* value;
        /* Verify that the binding is correct */
        ASSERT_TRUE(etor_rec_lookup(etor, a1, &value));
        EXPECT_EQ(i100, value);
        /* Now check the eval function */
        ASSERT_TRUE(identifier_eval_rec(a1, etor, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(identifier_checkClose_bound)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a1, OBJ(i100));
        struct Object* value = close_rec(OBJ(a1), etor);
        ASSERT_EQ(i100, value);
    END

    TEST(identifier_checkClose_unbound)
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value = close_rec(OBJ(a1), etor);
        ASSERT_EQ(a1, value);
    END

    TEST(identifier_checkAssign_newBinding)
        struct Etor_rec* etor = etor_rec_new();
        count_t envTopBefore = etor->env->nElems;
        ASSERT_TRUE(identifier_assign(a1, OBJ(i100), etor));
        ASSERT_IEQ(envTopBefore + 2, etor->env->nElems);
        struct Object* value;
        ASSERT_TRUE(etor_rec_lookup(etor, a1, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(identifier_checkAssign_rebind)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a1, OBJ(i100));
        struct Object* value;
        ASSERT_TRUE(etor_rec_lookup(etor, a1, &value));
        EXPECT_EQ(i100, value);
        count_t envTopBefore = etor->env->nElems;
        ASSERT_TRUE(identifier_assign(a1, OBJ(i200), etor));
        ASSERT_IEQ(envTopBefore, etor->env->nElems);
        ASSERT_TRUE(etor_rec_lookup(etor, a1, &value));
        EXPECT_EQ(i200, value);
    END

    END_TESTS
}

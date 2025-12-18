#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/types/identifier.h"
#include "object/types/quote.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* x = identifier_new("x");

    TEST(quote_checkConstruction)
        struct Quote* quote = quote_new(OBJ(x));
        ASSERT_ISA(OT_Quote, quote);
        ASSERT_IEQ(NWORDS(struct Quote), quote->obj.nWords);
        EXPECT_EQ(x, quote->expr);
    END

    TEST(quote_checkEval)
        struct Quote* quote = quote_new(OBJ(x));
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(quote), etor, &value));
        EXPECT_EQ(x, value);
    END

    TEST(quote_checkShow)
        struct Quote* quote = quote_new(OBJ(x));
        SHOW("Should show \"'x'\"", quote);
    END

    END_TESTS
}

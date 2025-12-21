#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/types/application.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/pair.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Etor_rec* etor = etor_rec_new();

    TEST(primitive_checkEvaluation_paramTypeMatch)
        struct Integer* i100 = integer_new(100);
        struct Integer* i200 = integer_new(200);
        struct Identifier* first = identifier_new("first");
        struct Pair* pair = pair_new(OBJ(i100), OBJ(i200));
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(pair)};
        struct Application* app = application_new(OBJ(first), nArgs, args);
        struct Object* closedAppObj = close_rec(OBJ(app), etor);
        SHOW("closed app", closedAppObj);
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(app), etor, &value));
        EXPECT_EQ(i100, value);
    END

    TEST(primitive_checkEvaluation_paramTypeNoMatch)
         struct Identifier* first = identifier_new("first");
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(g_nil)};
        struct Application* app = application_new(OBJ(first), nArgs, args);
        struct Object* closedAppObj = close_rec(OBJ(app), etor);
        SHOW("closed app", closedAppObj);
        struct Object* value;
        ASSERT_FALSE(eval_rec(OBJ(app), etor, &value));
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/types/application.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* f = identifier_new("f");
    struct Identifier* x = identifier_new("x");
    struct Integer* i100 = integer_new(100);

    TEST(application_checkConstruction)
        count_t nArgs = 0;
        struct Object* args[] = {};
        struct Application* app = application_new(OBJ(x), nArgs, args);
        ASSERT_ISA(OT_Application, app);
        ASSERT_IEQ(NWORDS(struct Application), app->obj.nWords);
        ASSERT_IEQ(0, app->nArgs);
    END

    TEST(application_checkEval)
        /* Create a function */
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(x);
        struct Etor_rec* etor = etor_rec_new();
        function_attachFinalRule(function, nParams, params, body);
        struct Object* value;
        ASSERT_TRUE(function_close_rec(function, etor, &value));
        /* Create an application */
        count_t nArgs = 1;
        struct Object* args[] = {OBJ(i100)};
        struct Application* app = application_new((struct Object*)function, nArgs, args);
        ASSERT_TRUE(eval_rec((struct Object*)app, etor, &value));
        EXPECT_EQ(i100, value);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/types/application.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/string.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(display_checkEvaluation)
        struct Etor_rec* etor = etor_rec_new();
        struct Identifier* x = identifier_new("x");
        struct Integer* i100 = integer_new(100);
        etor_rec_bind(etor, x, OBJ(i100));
        struct Identifier* display = identifier_new("display");
        count_t nArgs = 3;
        struct String* string = string_new("x = ");
        struct String* nl = string_new("\n");
        struct Object* args[] = {OBJ(string), OBJ(x), OBJ(nl)};
        struct Application* app = application_new(OBJ(display), nArgs, args);
        struct Object* closedAppObj = close_rec(OBJ(app), etor);
        SHOW("closed app", closedAppObj);
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(app), etor, &value));
        EXPECT_EQ(g_nil, value);
    END

    END_TESTS
}

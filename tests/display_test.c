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
        struct Identifier* display = identifier_new("display");
        count_t nArgs = 2;
        struct String* string = string_new("x = ");
        struct Integer* i100 = integer_new(100);
        struct Object* args[] = {OBJ(string), OBJ(i100)};
        struct Application* app = application_new(OBJ(display), nArgs, args);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* closedAppObj = close_rec(OBJ(app), etor);
        SHOW("closed app", closedAppObj);
    END

    END_TESTS
}

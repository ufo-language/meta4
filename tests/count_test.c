#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/types/application.h"
#include "object/types/array.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/pair.h"
#include "object/types/string.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Etor_rec* etor = etor_rec_new();
    struct Identifier* primName = identifier_new("count");

    TEST(count_checkEvaluation_array)
        struct Array* array = array_new_withElem(3, (struct Object*)g_nil);
        struct Object* args[] = {OBJ(array)};
        count_t nArgs = 1;
        struct Application* app = application_new(OBJ(primName), nArgs, args);
        struct Object* closedAppObj = close_rec(OBJ(app), etor);
        SHOW("closed app", closedAppObj);
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(app), etor, &value));
        EXPECT_ISA(OT_Integer, value);
        EXPECT_IEQ(3, ((struct Integer*)value)->i);
    END

    TEST(count_checkEvaluation_pair)
        struct Pair* pair = pair_new((struct Object*)g_nil, (struct Object*)g_nil);
        struct Object* args[] = {OBJ(pair)};
        count_t nArgs = 1;
        struct Application* app = application_new(OBJ(primName), nArgs, args);
        struct Object* closedAppObj = close_rec(OBJ(app), etor);
        SHOW("closed app", closedAppObj);
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(app), etor, &value));
        EXPECT_ISA(OT_Integer, value);
        EXPECT_IEQ(2, ((struct Integer*)value)->i);
    END

    END_TESTS
}

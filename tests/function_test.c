#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/function.h"
#include "object/types/identifier.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* f = identifier_new("f");
    struct Identifier* x = identifier_new("x");
    struct Identifier* y = identifier_new("y");

    TEST(function_checkConstruction)
        count_t nParams = 2;
        struct Object* params[] = {OBJ(x), OBJ(y)};
        struct Object* body = OBJ(g_nil);
        struct Function* function = function_new(f, nParams, params, body, g_emptyFunction);
        ASSERT_ISA(OT_Function, function);
    END

    END_TESTS
}

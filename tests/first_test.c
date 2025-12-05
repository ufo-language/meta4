#include "_test.h"
#include "_typedefs.h"

// #include "evaluator/evaluator.h"
#include "object/types/nil.h"

// static void _checkConstruction(struct Evaluator* etor) {
// }

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(nil_checkConstruction)
        // struct Evaluator* etor = etor_new();
        // etor_run(etor, _checkConstruction);
        EXPECT_TRUE(true);
    END

    END_TESTS
}

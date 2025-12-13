#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/match.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {

    BEGIN_TESTS

    struct Identifier* a = identifier_new("a");
    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(match_checkConstants)
        struct Vector* bindings = vector_new();
        ASSERT_IEQ(0, bindings->top);
        ASSERT_TRUE(match(OBJ(i100), OBJ(i100), bindings));
        ASSERT_FALSE(match(OBJ(i100), OBJ(i200), bindings));
    END

    TEST(match_checkIdentifiers)
        struct Vector* bindings = vector_new();
        ASSERT_IEQ(0, bindings->top);
        ASSERT_TRUE(match(OBJ(a), OBJ(i100), bindings));
        ASSERT_IEQ(2, bindings->top);
        struct Object* value;
        ASSERT_TRUE(vector_lookup(bindings, OBJ(a), &value));
        ASSERT_EQ(i100, value);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/globals.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);
    struct Identifier* a = identifier_new("a");
    struct Identifier* b = identifier_new("b");

    TEST(term_checkConstruction)
        struct Symbol* name = symbol_new("Term1");
        struct Object* attrib = (struct Object*)g_nil;
        count_t nArgs = 2;
        struct Object* args[] = {OBJ(i100), OBJ(i200)};
        struct Term* term = term_new(name, nArgs, args, attrib);
        ASSERT_ISA(OT_Term, term);
        ASSERT_IEQ(NWORDS(struct Term) + nArgs, term->obj.nWords);
        EXPECT_EQ(name, term->name);
        ASSERT_IEQ(nArgs, term->nArgs);
        EXPECT_EQ(i100, term->args[0]);
        EXPECT_EQ(i200, term->args[1]);
    END

    TEST(term_checkEval)
        struct Symbol* name = symbol_new("Term1");
        struct Object* attrib = (struct Object*)g_nil;
        count_t nArgs = 2;
        struct Object* args[] = {OBJ(a), OBJ(b)};
        struct Term* term = term_new(name, nArgs, args, attrib);
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, a, OBJ(i100));
        etor_rec_bind(etor, b, OBJ(i200));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(term), etor, &value));
        ASSERT_ISA(OT_Term, value);
        struct Term* newTerm = (struct Term*)value;
        ASSERT_IEQ(nArgs, newTerm->nArgs);
        EXPECT_EQ(i100, newTerm->args[0]);
        EXPECT_EQ(i200, newTerm->args[1]);
    END

    TEST(term_checkShow)
        struct Symbol* name = symbol_new("Term1");
        struct Object* attrib = (struct Object*)g_nil;
        count_t nArgs = 2;
        struct Object* args[] = {OBJ(i100), OBJ(i200)};
        struct Term* term = term_new(name, nArgs, args, attrib);
        EXPECT_SHOW("Term1{100, 200}%nil", term);
    END

    END_TESTS
}

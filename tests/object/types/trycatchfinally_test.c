#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_cps.h"
#include "object/globals.h"
#include "object/types/application.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/inc.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/sequence.h"
#include "object/types/trycatchfinally.h"
#include "object/types/variable.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Etor_rec* etor = etor_rec_new();
    index_t savedEnv = etor_rec_envSave(etor);

    struct IntVar* ivTry = intVar_new(0);
    struct IntVar* ivCatch = intVar_new(0);
    struct Variable* varCatch = variable_new(OBJ(g_nil));
    struct IntVar* ivFinally = intVar_new(0);

    struct Inc* incTry = inc_new(OBJ(ivTry));
    struct Inc* incCatch = inc_new(OBJ(ivCatch));
    struct Inc* incFinally = inc_new(OBJ(ivFinally));

    struct Integer* i100 = integer_new(100);
    struct Object* throwArgs[] = {OBJ(i100)};
    struct Identifier* throw = identifier_new("throw");
    struct Application* throwApp = application_new(OBJ(throw), 1, throwArgs);

    struct Function* funCatch0 = function_new(g_idNil);
    struct Object* params0[] = {OBJ(g_nil)};
    function_addlRule(funCatch0, 0, params0, OBJ(incCatch));
    function_close_rec(funCatch0, etor);

    struct Function* funCatch1 = function_new(g_idNil);
    struct Identifier* x = identifier_new("x");
    struct Object* params1[] = {OBJ(x)};
    function_addlRule(funCatch1, 1, params1, OBJ(incCatch));
    function_close_rec(funCatch1, etor);

    TEST(tryCatchFinally_checkConstruction)
        struct Object* tryExpr = OBJ(g_nil);
        struct Function* catchRules = function_new(g_idNil);
        struct Object* finallyExpr = OBJ(g_nil);
        struct TryCatchFinally* tcf = tryCatchFinally_new(tryExpr, catchRules, finallyExpr);
        ASSERT_ISA(OT_TryCatchFinally, tcf);
        ASSERT_IEQ(NWORDS(struct Object) + 3, tcf->obj.nWords);
        ASSERT_IEQ(NWORDS(struct TryCatchFinally), tcf->obj.nWords);
    END

    TEST(tryCatchFinally_checkTry)
        {  /* reset */
            ivTry->i = 0;
            ivCatch->i = 0;
            ivFinally->i = 0;
            varCatch->value = OBJ(g_nil);
            etor_rec_envRestore(etor, savedEnv);
        }
        struct TryCatchFinally* tcf = tryCatchFinally_new(OBJ(incTry), funCatch1, OBJ(incFinally));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(tcf), etor, &value));
        ASSERT_IEQ(1, ivTry->i);
        ASSERT_IEQ(0, ivCatch->i);
        ASSERT_IEQ(1, ivFinally->i);
    END

    TEST(tryCatchFinally_checkCatch_match)
        {  /* reset */
            ivTry->i = 0;
            ivCatch->i = 0;
            ivFinally->i = 0;
            varCatch->value = OBJ(g_nil);
            etor_rec_envRestore(etor, savedEnv);
        }
        struct Object* exprs[] = {OBJ(throwApp), OBJ(incTry)};
        struct Sequence* seq = sequence_new(2, exprs);
        struct TryCatchFinally* tcf = tryCatchFinally_new(OBJ(seq), funCatch1, OBJ(incFinally));
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(tcf), etor, &value));
        ASSERT_IEQ(0, ivTry->i);
        ASSERT_IEQ(1, ivCatch->i);
        ASSERT_IEQ(1, ivFinally->i);
    END

    TEST(tryCatchFinally_checkCatch_noMatch)
        {  /* reset */
            ivTry->i = 0;
            ivCatch->i = 0;
            ivFinally->i = 0;
            varCatch->value = OBJ(g_nil);
            etor_rec_envRestore(etor, savedEnv);
        }
        struct Object* exprs[] = {OBJ(throwApp), OBJ(incTry)};
        struct Sequence* seq = sequence_new(2, exprs);
        struct TryCatchFinally* tcf = tryCatchFinally_new(OBJ(seq), funCatch0, OBJ(incFinally));
        struct Object* value;
        ASSERT_FALSE(eval_rec(OBJ(tcf), etor, &value));
        ASSERT_IEQ(0, ivTry->i);
        ASSERT_IEQ(0, ivCatch->i);
        ASSERT_IEQ(1, ivFinally->i);
        ASSERT_EQ(i100, value);
    END

    END_TESTS
}

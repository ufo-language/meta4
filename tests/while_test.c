#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/globals.h"
#include "object/functions/eval_rec.h"
#include "object/types/dec.h"
#include "object/types/intvar.h"
#include "object/types/while.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(while_checkConstruction)
        struct While* while_ = while_new(OBJ(g_false), OBJ(g_nil));
        ASSERT_ISA(OT_While, while_);
        ASSERT_IEQ(NWORDS(struct While), while_->obj.nWords);
        EXPECT_EQ(while_->cond, g_false);
        EXPECT_EQ(while_->body, g_nil);
    END

    TEST(while_checkEval_false)
        struct While* while_ = while_new(OBJ(g_false), OBJ(g_nil));
        struct Object* value;
        struct Etor_rec* etor = etor_rec_new();
        ASSERT_TRUE(eval_rec(OBJ(while_), etor, &value));
        EXPECT_EQ(g_nil, value);
    END

    TEST(while_checkEval_intVar)
        struct IntVar* intVar = intVar_new(4);
        struct Object* cond = OBJ(intVar);
        struct Object* body = OBJ(dec_new(OBJ(intVar)));
        struct While* while_ = while_new(cond, body);
        struct Etor_rec* etor = etor_rec_new();
        struct Object* value;
        ASSERT_TRUE(eval_rec(OBJ(while_), etor, &value));
        EXPECT_ISA(OT_IntVar, value);
        EXPECT_IEQ(0, ((struct IntVar*)value)->i);
    END
    
    TEST(while_checkShow)
        struct While* while_ = while_new(OBJ(g_false), OBJ(g_nil));
        SHOW("should be 'while false nil'", while_);
    END

    END_TESTS
}

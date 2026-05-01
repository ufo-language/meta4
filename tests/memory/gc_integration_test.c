#include "_test.h"
#include "_typedefs.h"

#include "memory/gc.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/eval_rec.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/pair.h"
#include "object/types/vector.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(gc_during_evaluation)
        gc_setThreshold(g_gc, 30);
        
        struct Etor_rec* etor = etor_rec_new();
        gc_pushRoot(g_gc, (struct Object*)etor);
        
        struct Integer* i1 = integer_new(100);
        struct Integer* i2 = integer_new(200);
        struct Pair* pair = pair_new((struct Object*)i1, (struct Object*)i2);
        gc_pushRoot(g_gc, (struct Object*)pair);
        
        for (int i = 0; i < 50; i++) {
            integer_new(i * 1000);
        }
        
        struct Object* result;
        bool_t success = eval_rec((struct Object*)pair, etor, &result);
        
        EXPECT_TRUE(success);
        EXPECT_NOTNULL(result);
        
        gc_popRoots(g_gc, 2);
    END

    TEST(gc_stress_with_eval)
        gc_setThreshold(g_gc, 20);
        
        for (int iter = 0; iter < 10; iter++) {
            struct Integer* num = integer_new(100);
            gc_pushRoot(g_gc, (struct Object*)num);
            
            struct Etor_rec* etor = etor_rec_new();
            struct Object* result;
            bool_t evalSuccess = eval_rec((struct Object*)num, etor, &result);
            EXPECT_TRUE(evalSuccess);
            
            gc_popRoot(g_gc);
            
            for (int j = 0; j < 20; j++) {
                integer_new(j);
            }
        }
    END

    TEST(gc_preserves_objects_during_complex_operations)
        gc_setThreshold(g_gc, 25);
        
        struct Vector* results = vector_new();
        gc_pushRoot(g_gc, (struct Object*)results);
        
        for (int i = 0; i < 20; i++) {
            struct Integer* num = integer_new(42);
            
            struct Etor_rec* etor = etor_rec_new();
            struct Object* result;
            eval_rec((struct Object*)num, etor, &result);
            
            vector_push(results, result);
            
            for (int j = 0; j < 10; j++) {
                integer_new(j * 1000);
            }
        }
        
        EXPECT_IEQ(20, results->nElems);
        for (int i = 0; i < 20; i++) {
            struct Integer* num = (struct Integer*)vector_get_unsafe(results, i);
            EXPECT_IEQ(42, num->i);
        }
        
        gc_popRoot(g_gc);
    END

    TEST(gc_with_bindings)
        gc_setThreshold(g_gc, 30);
        
        struct Identifier* x = identifier_new("x");
        struct Integer* val = integer_new(123);
        
        struct Etor_rec* etor = etor_rec_new();
        gc_pushRoot(g_gc, (struct Object*)etor);
        
        etor_rec_bind(etor, x, (struct Object*)val);
        
        for (int i = 0; i < 50; i++) {
            integer_new(i * 1000);
        }
        
        struct Object* result;
        bool_t success = eval_rec((struct Object*)x, etor, &result);
        
        EXPECT_TRUE(success);
        EXPECT_ISA(OT_Integer, result);
        EXPECT_IEQ(123, ((struct Integer*)result)->i);
        
        gc_popRoot(g_gc);
    END

    END_TESTS
}

#include "_test.h"
#include "_typedefs.h"

#include "memory/gc.h"
#include "object/types/integer.h"
#include "object/types/pair.h"
#include "object/types/vector.h"
#include "object/types/array.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    TEST(gc_basic_allocation)
        gc_setThreshold(g_gc, 50);
        struct Integer* i1 = integer_new(100);
        struct Integer* i2 = integer_new(200);
        struct Integer* i3 = integer_new(300);
        EXPECT_NOTNULL(i1);
        EXPECT_NOTNULL(i2);
        EXPECT_NOTNULL(i3);
        EXPECT_IEQ(100, i1->i);
        EXPECT_IEQ(200, i2->i);
        EXPECT_IEQ(300, i3->i);
    END

    TEST(gc_root_stack)
        gc_setThreshold(g_gc, 50);
        struct Integer* i1 = integer_new(100);
        gc_pushRoot(g_gc, (struct Object*)i1);
        
        for (int i = 0; i < 100; i++) {
            integer_new(i);
        }
        
        gc_popRoot(g_gc);
        EXPECT_IEQ(100, i1->i);
    END

    TEST(gc_preserves_reachable_objects)
        gc_setThreshold(g_gc, 20);
        struct Integer* i1 = integer_new(100);
        struct Integer* i2 = integer_new(200);
        struct Pair* pair = pair_new((struct Object*)i1, (struct Object*)i2);
        
        gc_pushRoot(g_gc, (struct Object*)pair);
        
        for (int i = 0; i < 50; i++) {
            integer_new(i);
        }
        
        EXPECT_IEQ(100, ((struct Integer*)pair->first)->i);
        EXPECT_IEQ(200, ((struct Integer*)pair->rest)->i);
        
        gc_popRoot(g_gc);
    END

    TEST(gc_collects_garbage)
        gc_setThreshold(g_gc, 20);
        count_t beforeAlloc = g_gc->allocatedSinceGC;
        
        for (int i = 0; i < 50; i++) {
            integer_new(i);
        }
        
        EXPECT_TRUE(g_gc->allocatedSinceGC < beforeAlloc + 50);
    END

    TEST(gc_handles_vectors)
        gc_setThreshold(g_gc, 30);
        struct Vector* vec = vector_new();
        gc_pushRoot(g_gc, (struct Object*)vec);
        
        for (int i = 0; i < 10; i++) {
            struct Integer* num = integer_new(i * 10);
            vector_push(vec, (struct Object*)num);
        }
        
        for (int i = 0; i < 50; i++) {
            integer_new(i * 1000);
        }
        
        EXPECT_IEQ(10, vec->nElems);
        for (int i = 0; i < 10; i++) {
            struct Integer* num = (struct Integer*)vector_get_unsafe(vec, i);
            EXPECT_IEQ(i * 10, num->i);
        }
        
        gc_popRoot(g_gc);
    END

    TEST(gc_handles_nested_structures)
        gc_setThreshold(g_gc, 30);
        struct Vector* vec = vector_new();
        gc_pushRoot(g_gc, (struct Object*)vec);
        
        for (int i = 0; i < 5; i++) {
            struct Integer* i1 = integer_new(i);
            struct Integer* i2 = integer_new(i * 10);
            struct Pair* p = pair_new((struct Object*)i1, (struct Object*)i2);
            vector_push(vec, (struct Object*)p);
        }
        
        for (int i = 0; i < 50; i++) {
            integer_new(i * 1000);
        }
        
        EXPECT_IEQ(5, vec->nElems);
        for (int i = 0; i < 5; i++) {
            struct Pair* p = (struct Pair*)vector_get_unsafe(vec, i);
            EXPECT_IEQ(i, ((struct Integer*)p->first)->i);
            EXPECT_IEQ(i * 10, ((struct Integer*)p->rest)->i);
        }
        
        gc_popRoot(g_gc);
    END

    TEST(gc_stress_test)
        gc_setThreshold(g_gc, 50);
        struct Vector* vec = vector_new();
        gc_pushRoot(g_gc, (struct Object*)vec);
        
        for (int i = 0; i < 100; i++) {
            struct Integer* num = integer_new(i);
            vector_push(vec, (struct Object*)num);
            
            for (int j = 0; j < 10; j++) {
                integer_new(j * 1000);
            }
        }
        
        EXPECT_IEQ(100, vec->nElems);
        for (int i = 0; i < 100; i++) {
            struct Integer* num = (struct Integer*)vector_get_unsafe(vec, i);
            EXPECT_IEQ(i, num->i);
        }
        
        gc_popRoot(g_gc);
    END

    END_TESTS
}

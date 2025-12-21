#include "_test.h"
#include "_typedefs.h"

#include "object/types/integer.h"
#include "object/types/queue.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Integer* i100 = integer_new(100);
    struct Integer* i200 = integer_new(200);

    TEST(queue_checkConstruction)
        struct Queue* q = queue_new();
        ASSERT_ISA(OT_Queue, q);
        ASSERT_IEQ(NWORDS(struct Object) + 3, q->obj.nWords);
        ASSERT_IEQ(NWORDS(struct Queue), q->obj.nWords);
        EXPECT_IEQ(0, q->nElems);
    END

    TEST(queue_checkEnqDeq)
        struct Queue* q = queue_new();
        EXPECT_IEQ(0, queue_count(q));
        queue_enq(q, OBJ(i100));
        EXPECT_IEQ(1, queue_count(q));
        queue_enq(q, OBJ(i200));
        EXPECT_IEQ(2, queue_count(q));
        struct Object* elem;
        ASSERT_TRUE(queue_deq(q, &elem));
        EXPECT_IEQ(1, queue_count(q));
        EXPECT_EQ(i100, elem);
        ASSERT_TRUE(queue_deq(q, &elem));
        EXPECT_IEQ(0, queue_count(q));
        EXPECT_EQ(i200, elem);
    END

    END_TESTS
}

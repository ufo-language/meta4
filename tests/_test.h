#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// #include "object/globals.h"
// #include "object/interntable.h"
// #include "memory/memory.h"
#include "object/functions/show.h"
// #include "object/objecttypes.h"
#include "plx.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define NORMAL "\033[0m"

#define OBJ(obj) ((struct Object*)obj)

size_t __NPASS__ = 0;
size_t __NFAIL__ = 0;

#define GC_NEW() gc_new(1024, 8192);

#if 0
struct Environment;
struct T_Identifier;
void env_bind(struct Environment *env, struct T_Identifier* key, struct Object* value);

void t_env_bindEach(struct Environment* env, struct Object* objs[]) {
    size_t n = 0;
    while (objs[n]) {
        struct T_Identifier* key = (struct T_Identifier*)objs[n++];
        struct Object* value = objs[n++];
        env_bind(env, key, value);
    }
}
#endif

#define BEGIN_TESTS plx_startup();
#define END_TESTS fprintf(stdout, "Passed %lu Failed %lu\n", __NPASS__, __NFAIL__); plx_shutdown();

#define TEST(name) \
    fprintf(stderr, "[%sTEST%s] %s:\n", BLUE, NORMAL, #name); \
    do {

#define END } while (0);

#define EXPECT_PTREQ(expected, actual) \
    if ((void*)(expected) == (void*)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s == %s (%p == %p)\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s == %s (%p == %p)\n", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NFAIL__; \
    }

#define ASSERT_PTREQ(expected, actual) \
    if ((void*)(expected) == (void*)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s == %s (%p == %p)\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s == %s (%p == %p)\n", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NFAIL__; \
    }

#define EXPECT_PTRNE(expected, actual) \
    if ((void*)(expected) != (void*)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s != %s (%p != %p)\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s != %s (%p != %p)\n", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NFAIL__; \
    }

#define ASSERT_PTRNE(expected, actual) \
    if ((void*)(expected) != (void*)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s != %s (%p != %p)\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s != %s (%p != %p)\n", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual), (expected), (actual)); \
        ++__NFAIL__; \
    }

#define EXPECT_EQ(expected, actual) \
    if (OBJ((uintptr_t)(expected)) == OBJ((uintptr_t)(actual))) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s == %s\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s == %s, expected = ", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        show((struct Object*)expected, stderr); \
        fputs(" :: ", stderr); \
        fputs(typeName(((struct Object*)expected)->typeId), stderr); \
        fputs(", actual = ", stderr); \
        show((struct Object*)actual, stderr); \
        fputs(" :: ", stderr); \
        fputs(typeName(((struct Object*)actual)->typeId), stderr); \
        fputc('\n', stderr); \
        ++__NFAIL__; \
    }

#define ASSERT_EQ(expected, actual) \
    if (OBJ((uintptr_t)(expected)) == OBJ((uintptr_t)(actual))) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s == %s\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s == %s, expected = ", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        show((struct Object*)expected, stderr); \
        fputs(" :: ", stderr); \
        fputs(typeName(((struct Object*)expected)->typeId), stderr); \
        fputs(", actual = ", stderr); \
        show((struct Object*)actual, stderr); \
        fputs(" :: ", stderr); \
        fputs(typeName(((struct Object*)actual)->typeId), stderr); \
        fputc('\n', stderr); \
        ++__NFAIL__; \
        break; \
    }

#define EXPECT_IEQ(expected, actual) \
    if ((int64_t)(expected) == (int64_t)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %" PRId64 " == %s\n", GREEN, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %" PRId64 " == %s, actual = ", RED, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        fprintf(stderr, "%" PRId64 "\n", (int64_t)(actual)); \
        ++__NFAIL__; \
    }

#define ASSERT_IEQ(expected, actual) \
    if ((int64_t)(expected) == (int64_t)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %" PRId64 " == %s\n", GREEN, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %" PRId64 " == %s, actual = ", RED, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        fprintf(stderr, "%" PRId64 "\n", (int64_t)(actual)); \
        ++__NFAIL__; \
        break; \
    }

#define EXPECT_INE(expected, actual) \
    if ((int64_t)(expected) != (int64_t)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %" PRId64 " != %s\n", GREEN, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %" PRId64 " != %s, actual = ", RED, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        fprintf(stderr, "%" PRId64 "l\n", (int64_t)(actual)); \
        ++__NFAIL__; \
    }

#define ASSERT_INE(expected, actual) \
    if ((int64_t)(expected) != (int64_t)(actual)) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %" PRId64 " != %s\n", GREEN, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %" PRId64 " != %s, actual = ", RED, NORMAL, __FILE__, __LINE__, (int64_t)(expected), (#actual)); \
        fprintf(stderr, "%" PRId64 "\n", (int64_t)(actual)); \
        ++__NFAIL__; \
        break; \
    }

#define EXPECT_NE(expected, actual) \
    if (OBJ((uintptr_t)(expected)) != OBJ((uintptr_t)(actual))) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s != %s\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s != %s\n", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        ++__NFAIL__; \
    }

#define ASSERT_NE(expected, actual) \
    if (OBJ((uintptr_t)(expected)) != OBJ((uintptr_t)(actual))) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s != %s\n", GREEN, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s != %s\n", RED, NORMAL, __FILE__, __LINE__, (#expected), (#actual)); \
        ++__NFAIL__; \
        break; \
    }

#define EXPECT_TRUE(expr) \
    if (expr) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s is true\n", GREEN, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s is not true\n", RED, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NFAIL__; \
    }

#define ASSERT_TRUE(expr) \
    if (expr) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s is true\n", GREEN, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s is not true\n", RED, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NFAIL__; \
        break; \
    }

#define EXPECT_FALSE(expr) \
    if (!expr) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s is false\n", GREEN, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s is not false\n", RED, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NFAIL__; \
    }

#define ASSERT_FALSE(expr) \
    if (!expr) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s is false\n", GREEN, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s is not false\n", RED, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NFAIL__; \
        break; \
    }

#define EXPECT_NOTNULL(expr) \
    if (expr != NULL) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s is not null\n", GREEN, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s is null\n", RED, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NFAIL__; \
    }

#define ASSERT_NOTNULL(expr) \
    if (expr != NULL) { \
        fprintf(stderr, "[%sPASS%s] ✅ [%s:%d] %s is not null\n", GREEN, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NPASS__; \
    } \
    else { \
        fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] %s is null\n", RED, NORMAL, __FILE__, __LINE__, #expr); \
        ++__NFAIL__; \
        break; \
    }

#define FORCE_FAIL() \
    fprintf(stderr, "[%sFAIL%s] ❌ [%s:%d] forced failure\n", RED, NORMAL, __FILE__, __LINE__); \
    ++__NFAIL__; \
    break;

#define MESSAGE(message) \
    fprintf(stderr, "[%sMESG%s] ⏩ [%s:%d] ", CYAN, NORMAL, __FILE__, __LINE__); \
    fputs(message, stderr); \
    fputc('\n', stderr);

#define SHOW(message, obj) \
    fprintf(stderr, "[%sSHOW%s] ⏩ [%s:%d] ", CYAN, NORMAL, __FILE__, __LINE__); \
    fputs(message, stderr); \
    fputs(":\n       ⏩ ", stderr); \
    show((struct Object*)obj, stderr); \
    fputs("\n", stderr);

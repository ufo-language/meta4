#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
#include "object/primitives/defineprims.h"
#include "plx.h"
#include "object/functions/show.h"


/* Defines ------------------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

enum {
    N_10   =         10,
    N_100K =     100000,
    N_1M   =    1000000,
    N_10M  =   10000000,
    N_100M =  100000000,
    N_1B   = 1000000000,
    N      = N_100M
};

/* Forward declarations -----------------------------------------------------*/

void _program1(void);

/* Global variables ---------------------------------------------------------*/

/* Lifecycle functions ------------------------------------------------------*/

void plx_startup(void) {
    memory_init(DEFAULT_HEAP_SIZE);
    globals_init();
    definePrims_init(g_globalEnv);
}

void plx_shutdown(void) {
    globals_free();
    memory_free();
}

/* Public functions ---------------------------------------------------------*/

int plx_main(void) {
    printf("evaluator.main starting\n");
    plx_startup();
    _program1();
    plx_shutdown();
    return 0;
}

/* Private functions --------------------------------------------------------*/

#include "object/evaluator/etor_rec.h"
#include "object/types/dec.h"
#include "object/types/intvar.h"
#include "object/types/while.h"

void _program1(void) {
    struct IntVar* intVar = intVar_new(N);
    struct Dec* dec = dec_new((struct Object*)intVar);
    struct While* while_ = while_new((struct Object*)intVar, (struct Object*)dec);
    struct Etor_rec* etor = etor_rec_new();
    struct Object* value = (struct Object*)g_nil;
    if (!etor_rec_run(etor, (struct Object*)while_, &value)) {
        fputs("main _program1 error ", stderr);
        show(value, stderr);
        fputc('\n', stderr);
    }
    else {
        fputs("main _program1 final value = ", stderr);
        show(value, stderr);
        fputc('\n', stderr);
    }
}

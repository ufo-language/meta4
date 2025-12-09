#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
#include "plx.h"

/* Defines ------------------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

/* Forward declarations -----------------------------------------------------*/

/* Global variables ---------------------------------------------------------*/

/* Lifecycle functions ------------------------------------------------------*/

void plx_startup(void) {
    memory_init(DEFAULT_HEAP_SIZE);
    // internTable_init();
    globals_init();
}

void plx_shutdown(void) {
    globals_free();
    // internTable_free();
    memory_free();
}

/* Public functions ---------------------------------------------------------*/

int plx_main(void) {
    printf("evaluator.main starting\n");
    plx_startup();

    plx_shutdown();
    return 0;
}

/* Private functions --------------------------------------------------------*/

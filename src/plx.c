#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/globals.h"
#include "plx.h"

/* Defines ------------------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

/* Forward declarations -----------------------------------------------------*/

static void _init(void);

/* Global variables ---------------------------------------------------------*/

/* Lifecycle functions ------------------------------------------------------*/

void plx_startup(void) {
    memory_init(DEFAULT_HEAP_SIZE);
    // internTable_init();
    _init();
    globals_init();
}

void plx_shutdown(void) {
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

extern const struct InitFunction_handler __start_init_function;
extern const struct InitFunction_handler __stop_init_function;

__attribute__((used, section("init_function")))
static const struct InitFunction_handler h_plx_init = {"plx.c", NULL};

// __attribute__((used, section("init_function")))
static void _init(void) {
    for (const struct InitFunction_handler *h = &__start_init_function; h < &__stop_init_function; h++) {
        fprintf(stderr, "got init function for '%s'\n", h->name);
        // h->function(NULL, NULL);
    }
}

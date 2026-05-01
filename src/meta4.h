#pragma once

#include "_typedefs.h"

/* Defines ------------------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

typedef void (*InitFunction)(void);

struct InitFunction_handler {
    const char* name;
    InitFunction function;
};

/* Forward declarations -----------------------------------------------------*/

/* Global variables ---------------------------------------------------------*/

/* Lifecycle functions ------------------------------------------------------*/

/* Public functions ---------------------------------------------------------*/

int meta4_main(void);
void meta4_startup(void);
void meta4_shutdown(void);

/* Private functions --------------------------------------------------------*/

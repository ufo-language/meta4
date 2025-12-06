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

void plx_startup(void);
void plx_shutdown(void);

/* Private functions --------------------------------------------------------*/

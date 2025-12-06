#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Boolean;
struct GC;
struct Nil;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

extern struct Boolean* g_true;
extern struct Boolean* g_false;
extern struct GC* g_gc;
extern struct Nil* g_nil;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_init(void);

#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Boolean;
struct FunctionRule;
struct GC;
struct Identifier;
struct Nil;
struct Object;
struct Pair;
struct PrimitiveRule;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

extern struct Boolean*       g_false;
extern struct Boolean*       g_true;
extern struct FunctionRule*  g_emptyFunctionRule;
extern struct GC*            g_gc;
extern struct Identifier*    g_idNil;
extern struct Nil*           g_nil;
extern struct Object*        g_uniqueObject;  /* Used in testing and parsing */
extern struct Pair*          g_emptyPair;
extern struct PrimitiveRule* g_emptyPrimRule;
extern struct Vector*        g_globalEnv;
extern struct Vector*        g_identifierInternTable;
extern struct Vector*        g_symbolInternTable;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_free(void);
void globals_init(void);

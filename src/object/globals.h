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
struct OutStream;
struct Pair;
struct PrimitiveRule;
struct Triple;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

extern struct Boolean*       g_false;
extern struct Boolean*       g_true;
extern struct Triple*        g_emptyTriple;
extern struct FunctionRule*  g_emptyFunctionRule;
extern struct GC*            g_gc;
extern struct Identifier*    g_idNil;
extern struct Nil*           g_nil;
extern struct Object*        g_uniqueObject;  /* Used in testing and parsing */
extern struct Pair*          g_emptyPair;
extern struct PrimitiveRule* g_emptyPrimRule;
extern struct Triple*        g_emptyTriple;
extern struct Vector*        g_globalEnv;
extern struct HashTable*     g_identifierInternTable;
extern struct HashTable*     g_symbolInternTable;
extern struct OutStream*     g_stdout;
extern struct OutStream*     g_stderr;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_free(void);
void globals_init(void);

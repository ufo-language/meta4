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
struct Binding;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

extern struct Binding*       g_emptyBinding;
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
extern struct HashTable*     g_identifierInternTable;
extern struct HashTable*     g_symbolInternTable;
extern struct OutStream*     g_stdout;
extern struct OutStream*     g_stderr;

/* Symbols used by the lexer and parser */
extern struct Symbol*        g_symBoolean;
extern struct Symbol*        g_symEOI;
extern struct Symbol*        g_symIdentifier;
extern struct Symbol*        g_symInteger;
extern struct Symbol*        g_symNil;
extern struct Symbol*        g_symNone;
extern struct Symbol*        g_symOperator;
extern struct Symbol*        g_symReal;
extern struct Symbol*        g_symReserved;
extern struct Symbol*        g_symSpecial;
extern struct Symbol*        g_symString;
extern struct Symbol*        g_symSymbol;
extern struct Symbol*        g_symWord;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_free(void);
void globals_init(void);

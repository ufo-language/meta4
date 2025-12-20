#include "_typedefs.h"

#include "memory/gc.h"
#include "object/globals.h"
#include "object/types/binding.h"
#include "object/types/boolean.h"
#include "object/types/function.h"
#include "object/types/hashtable.h"
#include "object/types/identifier.h"
#include "object/types/nil.h"
#include "object/types/outstream.h"
#include "object/types/pair.h"
#include "object/types/primitive.h"
#include "object/types/symbol.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

struct Binding*       g_emptyBinding;
struct Boolean*       g_false;
struct Boolean*       g_true;
struct FunctionRule*  g_emptyFunctionRule;
struct GC*            g_gc;
struct Identifier*    g_idNil;
struct Nil*           g_nil;
struct Object*        g_uniqueObject;
struct Pair*          g_emptyPair;
struct PrimitiveRule* g_emptyPrimRule;
struct Vector*        g_globalEnv;
struct HashTable*     g_identifierInternTable;
struct HashTable*     g_symbolInternTable;
struct OutStream*     g_stdout;
struct OutStream*     g_stderr;

/* Symbols used by the lexer and parser */
struct Symbol*        g_symBoolean;
struct Symbol*        g_symEOI;
struct Symbol*        g_symIdentifier;
struct Symbol*        g_symInteger;
struct Symbol*        g_symNil;
struct Symbol*        g_symNone;
struct Symbol*        g_symOperator;
struct Symbol*        g_symReal;
struct Symbol*        g_symReserved;
struct Symbol*        g_symSpecial;
struct Symbol*        g_symString;
struct Symbol*        g_symSymbol;
struct Symbol*        g_symWord;

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void globals_free(void) {
    gc_free(g_gc);
}

void globals_init(void) {
    /* Memory & GC first */
    g_gc                    = gc_new();
    /* Prepare intern tables */
    g_emptyBinding          = binding_new_empty();
    g_identifierInternTable = hashTable_new();  /* Depends on g_emptyBinding */
    g_symbolInternTable     = hashTable_new();  /* Depends on g_emptyBinding */
    /* Create constants next */
    g_true                  = boolean_new(true);
    g_false                 = boolean_new(false);
    g_idNil                 = identifier_new("nil");
    g_nil                   = nil_new();
    g_uniqueObject          = object_new(OT_Null, NWORDS(*g_uniqueObject));
    g_stdout                = outStream_new_file(stdout);
    g_stderr                = outStream_new_file(stderr);
    /* Data structures next */
    g_emptyPair             = pair_new_empty();
    g_emptyFunctionRule     = function_emptyRule();
    g_emptyPrimRule         = prim_emptyRule();
    /* Lexer/parser symbols */
    g_symInteger            = symbol_new("Integer");
    g_symBoolean               = symbol_new("Bool");
    g_symEOI                = symbol_new("EOI");
    g_symIdentifier         = symbol_new("Identifeir");
    g_symInteger            = symbol_new("Integer");
    g_symNil                = symbol_new("Nil");
    g_symNone               = symbol_new("None");
    g_symOperator           = symbol_new("Operator");
    g_symReal               = symbol_new("Real");
    g_symReserved           = symbol_new("Reserved");
    g_symSpecial            = symbol_new("Special");
    g_symString             = symbol_new("String");
    g_symSymbol             = symbol_new("Symbol");
    g_symWord               = symbol_new("Word");
    /* Global environment last */
    g_globalEnv             = vector_new();
}

/* Private functions *********************************************************/

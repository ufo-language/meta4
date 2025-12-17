#include <ctype.h>
#include <string.h>

#include "lexer/lexer.h"

char* ReservedWords[] = {
  "do", "else", "end", "fun", "if", "in", "let", "letrec", "nothing", "then", "while",
  0
};

char* BoolWords[] = {
  "false", "true",
  0
};

char* NilWord = "nil";

static inline bool_t isany(ichar_t c)        { (void)c; return true; }
#if 0
static inline bool_t isdash(ichar_t c)       { return c == '-'; }
#endif
static inline bool_t isdot(ichar_t c)        { return c == '.'; }
static inline bool_t isdquote(ichar_t c)     { return c == '"'; }
static inline bool_t isnull(ichar_t c)       { return c == 0; }
static inline bool_t isoperator(ichar_t c)   { return (c != 0 && strchr("+-*/%<>!.:&", c)) ? true : false; }
static inline bool_t isunderscore(ichar_t c) { return c == '_'; }

#if 0
static inline bool_t isbindigit(ichar_t c)    { return c == '0' || c == '1'; }
/* also: isxdigit can be used for hex digits */
#endif

static struct Transition syntax_init[] = {
    {islower,      S_Word,  A_Keep,      T_None},
    {isupper,      S_Sym,   A_Keep,      T_None},
    {isdigit,      S_Int,   A_Keep,      T_None},
    {isdquote,     S_Str,   A_Skip,      T_None},
    {isspace,      S_Init,  A_Skip,      T_None},
    {isoperator,   S_Oper,  A_Keep,      T_None},
    {isnull,       S_Init,  A_Skip,      T_EOI},     /* C_NUL is end of input */
    {isany,        S_Init,  A_Keep,      T_Special}  /* C_ANY is wildcard */
};

static struct Transition syntax_int[] = {
    {isdigit,      S_Int,   A_Keep,      T_None},
    {isdot,        S_Point, A_Keep,      T_None},
    {isany,        S_Init,  A_Reuse,     T_Int}
};

static struct Transition syntax_point[] = {
    {isdigit,      S_Real,  A_Keep,      T_None},
    {isany,        S_Init,  A_RealErr,   T_None}
};

static struct Transition syntax_real[] = {
    {isdigit,      S_Real,  A_Keep,      T_None},
    {isany,        S_Init,  A_Reuse,     T_Real}
};

static struct Transition syntax_word[] = {
    {islower,      S_Word,  A_Keep,      T_None},
    {isupper,      S_Word,  A_Keep,      T_None},
    {isdigit,      S_Word,  A_Keep,      T_None},
    {isunderscore, S_Word,  A_Keep,      T_None},
    {isany,        S_Init,  A_Reuse,     T_Word}
};

static struct Transition syntax_string[] = {
    {isdquote,     S_Init,  A_Skip,      T_String},
    {isnull,       S_Init,  A_StringErr, T_None},
    {isany,        S_Str,   A_Keep,      T_None}
};

static struct Transition syntax_operator[] = {
    {isoperator,   S_Oper,  A_Keep,      T_None},
    {isany,        S_Init,  A_Reuse,     T_Oper}
};

static struct Transition syntax_symbol[] = {
    {islower,      S_Sym,  A_Keep,       T_None},
    {isupper,      S_Sym,  A_Keep,       T_None},
    {isunderscore, S_Sym,  A_Keep,       T_None},
    {isany,        S_Init, A_Reuse,      T_Symbol}
};

struct Transition* syntax[] = {
    [S_Init]  = syntax_init,
    [S_Int]   = syntax_int,
    [S_Point] = syntax_point,  /* transition from INT to REAL */
    [S_Real]  = syntax_real,
    [S_Word]  = syntax_word,
    [S_Str]   = syntax_string,
    [S_Oper]  = syntax_operator,
    [S_Sym]   = syntax_symbol
};

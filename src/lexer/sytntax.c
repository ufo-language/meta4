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

char* OperatorChars = "+-*/%<>!.:&";

static inline bool_t isany(ichar_t c)        { (void)c; return true; }
static inline bool_t isdquote(ichar_t c)     { return c == '"'; }
static inline bool_t isnull(ichar_t c)       { return c == 0; }
static inline bool_t isoperator(ichar_t c)   { return (c != 0 && strchr(OperatorChars, c)) ? true : false; }
static inline bool_t isunderscore(ichar_t c) { return c == '_'; }
/* numbers */
static inline bool_t isb(ichar_t c)          { return c == 'b' || c == 'B'; }
static inline bool_t isbdigit(ichar_t c)     { return c == '1' || c == '0'; }
static inline bool_t isdot(ichar_t c)        { return c == '.'; }
static inline bool_t issign(ichar_t c)       { return c == '-' || c == '+'; }
static inline bool_t isx(ichar_t c)          { return c == 'x' || c == 'X'; }
static inline bool_t iszero(ichar_t c)       { return c == '0'; }

/* The lexer expects that for any emittable token there must be a change out of the
   S_Init state into a new state. This is how it recognizes the starting position
   of the token. In particular the Special and EOI tokens could be handled right
   inside the Snit state like this:
       {isnull,       S_Init,    A_Skip,      T_EOI}
       {isany,        S_Init,    A_Keep,     T_Special}
   but then the lexer wouldn't detect a state change and save the correct start positions.
*/
static struct Transition syntax_init[] = {
    {islower,      S_Word,    A_Keep,      T_None},
    {isupper,      S_Sym,     A_Keep,      T_None},
    {iszero,       S_Zero,    A_Keep,      T_None},
    {isdigit,      S_Int,     A_Keep,      T_None},
    {isdquote,     S_Str,     A_Skip,      T_None},
    {isspace,      S_Init,    A_Skip,      T_None},
    {issign,       S_Sign,    A_Keep,      T_None},
    {isoperator,   S_Oper,    A_Keep,      T_None},
    {isnull,       S_EOI,     A_Reuse,     T_None},  /* isnull means end of input */
    {isany,        S_Special, A_Reuse,     T_None}   /* isany is a wildcard */
};

static struct Transition syntax_eoi[] = {
    {isnull,       S_EOI,    A_Skip,       T_EOI}
};

static struct Transition syntax_special[] = {
    {isany,        S_Init,    A_Keep,      T_Special}
};

static struct Transition syntax_int[] = {
    {isdigit,      S_Int,     A_Keep,      T_None},
    {isdot,        S_Point,   A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_Int}
};

static struct Transition syntax_hexInt[] = {
    {isxdigit,     S_HexInt,  A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_HexInt}
};

static struct Transition syntax_binInt[] = {
    {isbdigit,     S_BinInt,  A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_BinInt}
};

static struct Transition syntax_sign[] = {
    {iszero,       S_Zero,    A_Keep,      T_None},
    {isdigit,      S_Int,     A_Keep,      T_None},
    {isany,        S_Oper,    A_Keep,      T_None}
};

static struct Transition syntax_zero[] = {
    {isx,          S_HexInt,  A_Skip,      T_None},
    {isb,          S_BinInt,  A_Skip,      T_None},
    {isany,        S_Init,    A_Reuse,     T_Int}
};

static struct Transition syntax_point[] = {
    {isdigit,      S_Real,    A_Keep,      T_None},
    {isany,        S_Init,    A_RealErr,   T_None}
};

static struct Transition syntax_real[] = {
    {isdigit,      S_Real,    A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_Real}
};

static struct Transition syntax_word[] = {
    {islower,      S_Word,    A_Keep,      T_None},
    {isupper,      S_Word,    A_Keep,      T_None},
    {isdigit,      S_Word,    A_Keep,      T_None},
    {isunderscore, S_Word,    A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_Word}
};

static struct Transition syntax_string[] = {
    {isdquote,     S_Init,    A_Skip,      T_String},
    {isnull,       S_Init,    A_StringErr, T_None},
    {isany,        S_Str,     A_Keep,      T_None}
};

static struct Transition syntax_operator[] = {
    {isoperator,   S_Oper,    A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_Oper}
};

static struct Transition syntax_symbol[] = {
    {islower,      S_Sym,     A_Keep,      T_None},
    {isupper,      S_Sym,     A_Keep,      T_None},
    {isunderscore, S_Sym,     A_Keep,      T_None},
    {isany,        S_Init,    A_Reuse,     T_Symbol}
};

struct Transition* syntax[] = {
    [S_Init]    = syntax_init,
    [S_EOI]     = syntax_eoi,
    [S_Special] = syntax_special,
    [S_Int]     = syntax_int,
    [S_HexInt]  = syntax_hexInt,
    [S_BinInt]  = syntax_binInt,
    [S_Sign]    = syntax_sign,
    [S_Point]   = syntax_point,  /* Transition from INT to REAL */
    [S_Real]    = syntax_real,
    [S_Word]    = syntax_word,
    [S_Str]     = syntax_string,
    [S_Oper]    = syntax_operator,
    [S_Sym]     = syntax_symbol,
    [S_Zero]    = syntax_zero
};

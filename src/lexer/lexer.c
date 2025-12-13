#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static int_t _stringToInt(char* string, count_t len, int base);

/* Global variables **********************************************************/

enum {
    C_OTHER = 0,
    C_ALPHA,
    C_DIGIT,
    C_WS,
    C_OPER
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winitializer-overrides"
/* This warning is disabled because the charClassTable defines values twice:
   Once with the '[0 ... 255] = C_OTHER' clause, and then below that it
   re-defines specific values.
*/

int charType[256] = {
    [0 ... 255] = C_OTHER,

    /* whitespace */
    [' ']  = C_WS,
    ['\t'] = C_WS,
    ['\n'] = C_WS,
    ['\r'] = C_WS,
    ['\f'] = C_WS,
    ['\v'] = C_WS,

    /* digits */
    ['0'] = C_DIGIT, ['1'] = C_DIGIT, ['2'] = C_DIGIT, ['3'] = C_DIGIT,
    ['4'] = C_DIGIT, ['5'] = C_DIGIT, ['6'] = C_DIGIT, ['7'] = C_DIGIT,
    ['8'] = C_DIGIT, ['9'] = C_DIGIT,

    /* uppercase alpha */
    ['A'] = C_ALPHA, ['B'] = C_ALPHA, ['C'] = C_ALPHA, ['D'] = C_ALPHA,
    ['E'] = C_ALPHA, ['F'] = C_ALPHA, ['G'] = C_ALPHA, ['H'] = C_ALPHA,
    ['I'] = C_ALPHA, ['J'] = C_ALPHA, ['K'] = C_ALPHA, ['L'] = C_ALPHA,
    ['M'] = C_ALPHA, ['N'] = C_ALPHA, ['O'] = C_ALPHA, ['P'] = C_ALPHA,
    ['Q'] = C_ALPHA, ['R'] = C_ALPHA, ['S'] = C_ALPHA, ['T'] = C_ALPHA,
    ['U'] = C_ALPHA, ['V'] = C_ALPHA, ['W'] = C_ALPHA, ['X'] = C_ALPHA,
    ['Y'] = C_ALPHA, ['Z'] = C_ALPHA,

    /* lowercase alpha */
    ['a'] = C_ALPHA, ['b'] = C_ALPHA, ['c'] = C_ALPHA, ['d'] = C_ALPHA,
    ['e'] = C_ALPHA, ['f'] = C_ALPHA, ['g'] = C_ALPHA, ['h'] = C_ALPHA,
    ['i'] = C_ALPHA, ['j'] = C_ALPHA, ['k'] = C_ALPHA, ['l'] = C_ALPHA,
    ['m'] = C_ALPHA, ['n'] = C_ALPHA, ['o'] = C_ALPHA, ['p'] = C_ALPHA,
    ['q'] = C_ALPHA, ['r'] = C_ALPHA, ['s'] = C_ALPHA, ['t'] = C_ALPHA,
    ['u'] = C_ALPHA, ['v'] = C_ALPHA, ['w'] = C_ALPHA, ['x'] = C_ALPHA,
    ['y'] = C_ALPHA, ['z'] = C_ALPHA,

    /* operators */
    ['!'] = C_OPER, ['#'] = C_OPER, ['$'] = C_OPER,
    ['%'] = C_OPER, ['&'] = C_OPER,
    ['*'] = C_OPER, ['+'] = C_OPER, [','] = C_OPER,
    ['-'] = C_OPER, ['.'] = C_OPER, ['/'] = C_OPER, [':'] = C_OPER,
    ['<'] = C_OPER, ['='] = C_OPER, ['>'] = C_OPER,
    ['?'] = C_OPER, ['@'] = C_OPER,
    ['^'] = C_OPER, ['_'] = C_OPER,
    ['|'] = C_OPER, ['~'] = C_OPER,
};
#pragma clang diagnostic pop

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

enum TokenType {
    TOK_INT,
    TOK_FLOAT,
    TOK_IDENT,
    TOK_SYMBOL,
    TOK_STRING,
    TOK_OPERATOR,
    TOK_SPECIAL,
    TOK_EOF
};

struct Token {
    enum TokenType type;
    const char* start;
    count_t length;
};

/* static inline int isAlpha(int c) { return charType[c] == C_ALPHA; } */
static inline int isDigit(int c) { return charType[c] == C_DIGIT; }
static inline int isAlNum(int c) { return charType[c] == C_ALPHA || charType[c] == C_DIGIT; }
static inline int isWs(int c)    { return charType[c] == C_WS; }
static inline int isOper(int c) { return charType[c] == C_OPER; }

struct Token lexer_nextToken(const char** pcur) {
    const char* p = *pcur;

restart:
    /* skip whitespace */
    while (isWs(*p)) p++;

    /* end of input */
    if (*p == 0) {
        *pcur = p;
        return (struct Token){TOK_EOF, p, 0};
    }

    /* comments */
    if (p[0] == '/' && p[1] == '*') {
        p += 2;
        while (p[0] && !(p[0] == '*' && p[1] == '/')) p++;
        if (p[0]) p += 2;
        goto restart;
    }

    if (p[0] == '/' && p[1] == '/') {
        p += 2;
        while (*p && *p != '\n') p++;
        goto restart;
    }

    const char* start = p;

    /* strings */
    if (*p == '"') {
        p++;
        while (*p && *p != '"') {
            if (*p == '\\' && p[1]) p += 2;
            else p++;
        }
        if (*p == '"') p++;
        *pcur = p;
        return (struct Token){TOK_STRING, start, (int)(p - start)};
    }

    /* leading minus? */
    /* int neg = 0; */
    if (*p == '-') {
        /*neg = 1;*/
        p++;
    }

    /* number? */
    if (isDigit(*p)) {
        const char* q = p;

        /* base prefixes */
        int base = 10;
        if (*q == '0') {
            if (q[1] == 'x' || q[1] == 'X') {
                base = 16;
                q += 2;
                while (isDigit(*q) || (*q >= 'a' && *q <= 'f') || (*q >= 'A' && *q <= 'F')) q++;
                *pcur = q;
                return (struct Token){TOK_INT, start, (int)(q - start), };
            }
            if (q[1] == 'b' || q[1] == 'B') {
                base = 2;
                q += 2;
                while (*q == '0' || *q == '1') q++;
                *pcur = q;
                return (struct Token){TOK_INT, start, (int)(q - start)};
            }
        }

        /* decimal: int or float */
        while (isDigit(*q)) q++;

        int is_float = 0;

        if (*q == '.') {
            is_float = 1;
            q++;
            while (isDigit(*q)) q++;
        }

        *pcur = q;
        return (struct Token){is_float ? TOK_FLOAT : TOK_INT, start, (int)(q - start)};
    }

    /* identifier: [a-z_] ... */
    if ((*start >= 'a' && *start <= 'z') || *start == '_') {
        p++;
        while (isAlNum(*p) || *p == '_') p++;
        *pcur = p;
        return (struct Token){TOK_IDENT, start, p - start};
    }

    /* symbol: [A-Z] ... */
    if (*start >= 'A' && *start <= 'Z') {
        p++;
        while (isAlNum(*p) || *p == '_') p++;
        *pcur = p;
        return (struct Token){TOK_SYMBOL, start, (int)(p - start)};
    }

    /* operator: run of C_PUNCT chars */
    if (isOper(*start)) {
        p++;
        while (isOper(*p)) p++;
        *pcur = p;
        return (struct Token){TOK_OPERATOR, start, (int)(p - start)};
    }

    /* special: single C_OTHER */
    p++;
    *pcur = p;
    return (struct Token){TOK_SPECIAL, start, 1};
}

void lexer_lexAll(const char* src) {
    const char* p = src;
    for (;;) {
        struct Token token = lexer_nextToken(&p);
        if (token.type == TOK_EOF) break;
        printf("Token type = %d, %.*s\n", token.type, (int)token.length, token.start);
    }
}

/* Object functions ******************/

/* Private functions *********************************************************/

static int_t _stringToInt(char* string, count_t len, int base) {
    int_t v = 0;
    for (index_t i=0; i<len; ++i) {
        int d;
        char c = string[i];

        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
        else break;

        if (d >= base) break;
        v = v * base + d;
    }
    return v;
}

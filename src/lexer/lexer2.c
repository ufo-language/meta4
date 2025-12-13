#include <stdio.h>

#include "_typedefs.h"

#include "lexer/lexer2.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum CharType {
    C_SPECIAL = 0,
    C_ALPHA,
    C_DIGIT,
    C_WS,
    C_OPER
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winitializer-overrides"
/* The warning is disabled because the charClassTable defines values twice:
   Once with the '[0 ... 255] = C_OTHER' clause, and then below that it
   re-defines specific values.
*/

enum CharType charType[256] = {
    [0 ... 255] = C_SPECIAL,

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

void lexer2_lexAll(const char* string) {
    const char* p = string;
    for (;;) {
        struct LexerToken token = lexer_nextToken(&p);
        if (token.type == TOK_EOF) {
            break;
        }
        if (token.type >= TOK_ERROR) {
            fputs("lexer2_lexAll error\n", stderr);
            break;
        }
        switch (token.type) {
            case TOK_INT: fprintf(stderr, "TOK_INT\n"); break;
            case TOK_FLOAT: fprintf(stderr, "TOK_FLOAT\n"); break;
            case TOK_IDENT: fprintf(stderr, "TOK_IDENT\n"); break;
            case TOK_SYMBOL: fprintf(stderr, "TOK_SYMBOL\n"); break;
            case TOK_STRING: fprintf(stderr, "TOK_STRING\n"); break;
            case TOK_OPERATOR: fprintf(stderr, "TOK_OPERATOR\n"); break;
            case TOK_SPECIAL: fprintf(stderr, "TOK_SPECIAL\n"); break;
            case TOK_EOF: fprintf(stderr, "TOK_EOF\n"); break;
            case TOK_ERROR: fprintf(stderr, "TOK_ERROR\n"); break;
        }
        printf("Token type = %d, %.*s\n", token.type, (int)token.length, token.start);
    }
}

enum LexerState {
    LS_Init,
};

struct LexerToken lexer_nextToken(const char** pcur) {
    enum LexerState lexerState = LS_Init;
    const char* p = *pcur;
    enum TokenType tokenType = TOK_ERROR;

    bool_t contin = true;
    while (contin) {
        char c = *p++;
        if (c == 0) {
            break;
        }
        printf("lexer_nextToken loop c = '%c' (%d)\n", c, c);
        switch (lexerState) {
            case LS_Init:
                switch (charType[(int)c]) {
                    case C_WS:
                        /* Continue with next character */
                        break;
                    case C_SPECIAL:
                        tokenType = TOK_SPECIAL;
                        contin = false;
                        break;
                    case C_ALPHA:
                        break;
                    case C_DIGIT:
                        break;
                    case C_OPER:
                        break;
                }
            break;
        }
    }

    /* return a token */

}

/* Object functions ******************/

/* Private functions *********************************************************/

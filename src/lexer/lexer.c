#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "lexer/chartypes.h"
#include "lexer/lexer.h"
#include "lexer/reservedwords.h"
#include "object/types/identifier.h"
#include "object/types/intarray.h"
#include "object/types/integer.h"
#include "object/types/real.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static struct LexerToken _lexer_nextToken(const char** pcur, index_t* index, index_t* line, index_t* col);
static int_t _lexer_stringToBinInt(char* string);
static int_t _lexer_stringToDecInt(char* string);
static int_t _lexer_stringToHexInt(char* string);
static real_t _lexer_stringToReal(char* string);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* static inline int isAlpha(int c) { return charType[c] == C_ALPHA; } */
static inline int _lexer_isDigit(int c) { return charType[c] == C_DIGIT; }
static inline int _lexer_isAlNum(int c) { return charType[c] == C_ALPHA || charType[c] == C_DIGIT; }
static inline int _lexer_isWs(int c)    { return charType[c] == C_WS; }
static inline int _lexer_isOper(int c)  { return charType[c] == C_OPER; }

/* The lexeme limit is LEXER_BUFFER_SIZE - 1 */
enum { LEXER_BUFFER_SIZE = 512 };

/* This is 3 memory allocations for each token: Symbol, IntArray, Term.
   Can it be improved somehow?
*/
struct Term* _lexer_termToken(const string_t name, struct Object* value, index_t index, index_t line, index_t col) {
    struct Symbol* tokenName = symbol_new(name);
    int_t posInts[] = {index, line, col};
    struct IntArray* pos = intArray_new_elems(3, posInts);
    struct Object* args[] = {value};
    return term_new(tokenName,
                    (struct Object*)pos,
                    1, args);
}

bool_t lexer_lexAll(const char* sourceString, struct Vector* tokens) {
    const char* p = sourceString;
    bool_t contin = true;
    char buffer[LEXER_BUFFER_SIZE];
    index_t index = 0;
    index_t line = 1;
    index_t col = 1;
    while (contin) {
        struct LexerToken token = _lexer_nextToken(&p, &index, &line, &col);
        count_t nChars = token.length;
        if (nChars >= LEXER_BUFFER_SIZE) {
            nChars = LEXER_BUFFER_SIZE - 1;
        }
        strncpy(buffer, token.start, nChars);
        buffer[nChars] = 0;
        printf("Token type = %d, '%s'\n", token.type, buffer);
        switch (token.type) {
            case TOK_INT_DEC: {
                    int_t i = _lexer_stringToDecInt(buffer);
                    struct Integer* integer = integer_new(i);
                    struct Term* termToken = _lexer_termToken("Integer", (struct Object*)integer, index, line, col);
                    vector_push(tokens, (struct Object*)termToken);
                }
                break;
            case TOK_INT_HEX: {
                    int_t i = _lexer_stringToHexInt(buffer);
                    struct Integer* integer = integer_new(i);
                    vector_push(tokens, (struct Object*)integer);
                }
                break;
            case TOK_INT_BIN: {
                    int_t i = _lexer_stringToBinInt(buffer);
                    struct Integer* integer = integer_new(i);
                    vector_push(tokens, (struct Object*)integer);
                }
                break;
            case TOK_FLOAT: {
                    real_t r = _lexer_stringToReal(buffer);
                    struct Real* real = real_new(r);
                    vector_push(tokens, (struct Object*)real);
                }
                break;
            case TOK_IDENT: {
                    struct Identifier* ident = identifier_new(buffer);
                    vector_push(tokens, (struct Object*)ident);
                }
                break;
            case TOK_SYMBOL: {
                    struct Symbol* symbol = symbol_new(buffer);
                    vector_push(tokens, (struct Object*)symbol);
                }
                break;
            case TOK_STRING:
                break;
            case TOK_OPERATOR:
                break;
            case TOK_SPECIAL:
                break;
            case TOK_EOF:
                contin = false;
                break;
        }
    }
    return true;
}

/* Object functions ******************/

/* Private functions *********************************************************/

static struct LexerToken _lexer_nextToken(const char** pcur, index_t* index, index_t* line, index_t* col) {
    const char* p = *pcur;

RESTART:
    /* skip whitespace */
    while (_lexer_isWs(*p)) p++;

    /* end of input */
    if (*p == 0) {
        *pcur = p;
        return (struct LexerToken){TOK_EOF, p, 0, *index, *line, *col};
    }

    /* comments */
    if (p[0] == '/' && p[1] == '*') {
        p += 2;
        while (p[0] && !(p[0] == '*' && p[1] == '/')) p++;
        if (p[0]) p += 2;
        goto RESTART;
    }

    if (p[0] == '/' && p[1] == '/') {
        p += 2;
        while (*p && *p != '\n') p++;
        goto RESTART;
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
        return (struct LexerToken){TOK_STRING, start, (int)(p - start), *index, *line, *col};
    }

    /* leading minus? */
    /* int neg = 0; */
    if (*p == '-') {
        /*neg = 1;*/
        p++;
    }

    /* number? */
    if (_lexer_isDigit(*p)) {
        const char* q = p;

        /* base prefixes */
        if (*q == '0') {
            if (q[1] == 'x' || q[1] == 'X') {
                q += 2;
                while (_lexer_isDigit(*q) || (*q >= 'a' && *q <= 'f') || (*q >= 'A' && *q <= 'F')) q++;
                *pcur = q;
                return (struct LexerToken){TOK_INT_HEX, start, (int)(q - start), *index, *line, *col};
            }
            if (q[1] == 'b' || q[1] == 'B') {
                q += 2;
                while (*q == '0' || *q == '1') q++;
                *pcur = q;
                return (struct LexerToken){TOK_INT_BIN, start, (int)(q - start), *index, *line, *col};
            }
        }

        /* decimal: int or float */
        while (_lexer_isDigit(*q)) q++;

        int is_float = 0;

        if (*q == '.') {
            is_float = 1;
            q++;
            while (_lexer_isDigit(*q)) q++;
        }

        *pcur = q;
        return (struct LexerToken){is_float ? TOK_FLOAT : TOK_INT_DEC, start, (int)(q - start), *index, *line, *col};
    }

    /* identifier: [a-z_] ... */
    if ((*start >= 'a' && *start <= 'z') || *start == '_') {
        p++;
        while (_lexer_isAlNum(*p) || *p == '_') p++;
        *pcur = p;
        /* TODO identify reserved words */
        return (struct LexerToken){TOK_IDENT, start, p - start, *index, *line, *col};
    }

    /* symbol: [A-Z] ... */
    if (*start >= 'A' && *start <= 'Z') {
        p++;
        while (_lexer_isAlNum(*p) || *p == '_') p++;
        *pcur = p;
        return (struct LexerToken){TOK_SYMBOL, start, (int)(p - start), *index, *line, *col};
    }

    /* operator: run of C_PUNCT chars */
    if (_lexer_isOper(*start)) {
        p++;
        while (_lexer_isOper(*p)) p++;
        *pcur = p;
        return (struct LexerToken){TOK_OPERATOR, start, (int)(p - start), *index, *line, *col};
    }

    /* special: single C_OTHER */
    p++;
    *pcur = p;
    return (struct LexerToken){TOK_SPECIAL, start, 1, *index, *line, *col};
}

static int_t _lexer_stringToBinInt(char* string) {
    int_t sign = 1;
    switch (*string) {
        case '-':
            sign = -1;
            ++string;
            break;
        case '+':
            sign = 1;
            ++string;
            break;
        case '0':
            ++string;
            break;
        default:
            break;
    }
    assert(*string == 'b' || *string == 'B');
    ++string;  /* skip 'B' */
    int_t v = 0;
    while (*string) {
        char c = *string++;
        int d;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
        else break;
        v = v * 2 + d;
    }
    return sign * v;
}

static int_t _lexer_stringToDecInt(char* string) {
    int_t sign = 1;
    switch (*string) {
        case '-':
            sign = -1;
            ++string;
            break;
        case '+':
            sign = 1;
            ++string;
            break;
        default:
            break;
    }
    int_t v = 0;
    while (*string) {
        char c = *string++;
        int d;
        if (c >= '0' && c <= '9') d = c - '0';
        else break;
        v = v * 10 + d;
    }
    return sign * v;
}

static int_t _lexer_stringToHexInt(char* string) {
    int_t sign = 1;
    switch (*string) {
        case '-':
            sign = -1;
            ++string;
            break;
        case '+':
            sign = 1;
            ++string;
            break;
        case '0':
            ++string;
            break;
        default:
            break;
    }
    assert(*string == 'x' || *string == 'X');
    ++string;  /* skip 'X' */
    int_t v = 0;
    while (*string) {
        char c = *string++;
        int d;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
        else break;
        v = v * 16 + d;
    }
    return sign * v;
}

static real_t _lexer_stringToReal(char* string) {
    real_t value = 0.0;
    sscanf(string, "%lf", &value); // parse double
    return value;
}

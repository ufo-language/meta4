#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "lexer/lexer.h"
#include "object/globals.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/intarray.h"
#include "object/types/real.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct LexerFields {
    struct Transition** syntax;
    const string_t sourceString;
    string_t currentString;
    enum Lexer_TokenType tokenType;
    index_t indexPos;
    index_t linePos;
    index_t colPos;
    index_t startIndexPos;
    index_t startLinePos;
    index_t startColPos;
    count_t lexemeLen;
    char lexemeBuffer[Lexer_LexemeSize];
};

/* Forward declarations ******************************************************/

static enum Lexer_TokenType _lexer_classifyWord(char* s);
static void _lexer_createTokenTypeNames(void);
static struct Object* _lexer_lexemeToObject(enum Lexer_TokenType tokenType, string_t lexeme);
static enum Lexer_LexResult _lexer_nextToken(struct LexerFields* lexerFields);

/* Global variables **********************************************************/

extern char* ReservedWords[];
extern char* BoolWords[];
extern char* NilWord;

static bool_t tokenTypeNamesCreated = false;
static struct Symbol* tokenTypeNames[T_Final];

#if 0
char* lexerStateNames[] = {
    "Init", "Int", "HexInt", "BinInt", "Sign", "Point", "Real", "Word", "Str", "Oper", "Sym", "Zero"
};
#endif

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/
struct Vector* lexer_lexAll(struct Transition** syntax, const string_t sourceString) {
    struct Vector* tokens = vector_new();
    lexer_lexAll_withVector(syntax, sourceString, tokens);
    return tokens;
}

struct Vector* lexer_lexAll_withVector(struct Transition** syntax, const string_t sourceString, struct Vector* tokens) {
    if (!tokenTypeNamesCreated) {
        _lexer_createTokenTypeNames();
    }
    struct LexerFields lexerFields = {
        .syntax        = syntax,
        .sourceString  = sourceString,
        .currentString = sourceString,
        .tokenType     = T_None,
        .indexPos      = 0,
        .linePos       = 1,
        .colPos        = 1,
        .startIndexPos = 0,
        .startLinePos  = 1,
        .startColPos   = 1,
        .lexemeLen     = 0
    };
    for (;;) {
        enum Lexer_LexResult res = _lexer_nextToken(&lexerFields);
        #if 0
        fprintf(stderr, "lexer_lexAll got token %d '%s'\n", tokenType, lexemeBuffer);
        #endif
        switch (res) {
            case Lexer_Success: {
                    struct Symbol* tokenTermName = tokenTypeNames[lexerFields.tokenType];
                    struct Object* lexemeObj = _lexer_lexemeToObject(lexerFields.tokenType, lexerFields.lexemeBuffer);
                    struct Object* attrib = (struct Object*)intArray_new3(lexerFields.startIndexPos, lexerFields.startLinePos, lexerFields.startColPos);
                    struct Term* tokenTerm = term_new_1arg(tokenTermName, lexemeObj, attrib);
                    vector_push(tokens, (struct Object*)tokenTerm);
                    if (lexerFields.tokenType == T_EOI) {
                        return tokens;
                    }
                }
                break;
            case Lexer_UnknownError:
                fprintf(stderr, "ERROR: lexer_lexAll got an unknown error %d\n", res);
                return tokens;
            case Lexer_StringError:
                fprintf(stderr, "ERROR: lexer_lexAll got a string error %d\n", res);
                return tokens;
            case Lexer_RealError:
                fprintf(stderr, "ERROR: lexer_lexAll got an real-number error %d\n", res);
                return tokens;
            case Lexer_CommentError:
                fprintf(stderr, "ERROR: lexer_lexAll got a comment error %d\n", res);
                return tokens;
            default:
                fprintf(stderr, "ERROR: lexer_lexAll unhandled lex result %d\n", res);
                assert(false);
                return tokens;
        }
    }
    return tokens;
}

/* Object functions ******************/

/* Private functions *********************************************************/

static enum Lexer_TokenType _lexer_classifyWord(char* s) {
    for (char** w=ReservedWords; *w; ++w) {
        if (!strcmp(*w, s)) {
            return T_Reserved;
        }
    }
    for (char** w = BoolWords; *w; ++w) {
        if (!strcmp(*w, s)) {
            return T_Bool;
        }
    }
    if (!strcmp(NilWord, s)) {
        return T_Nil;
    }
    return T_Ident;
}

static void _lexer_createTokenTypeNames(void) {
    tokenTypeNames[T_None]     = g_symNone;
    tokenTypeNames[T_Int]      = g_symInteger;
    tokenTypeNames[T_HexInt]   = g_symInteger;
    tokenTypeNames[T_BinInt]   = g_symInteger;
    tokenTypeNames[T_Real]     = g_symReal;
    tokenTypeNames[T_Bool]     = g_symBoolean;
    tokenTypeNames[T_Nil]      = g_symNil;
    tokenTypeNames[T_Word]     = g_symWord;
    tokenTypeNames[T_Ident]    = g_symIdentifier;
    tokenTypeNames[T_Reserved] = g_symReserved;
    tokenTypeNames[T_String]   = g_symString;
    tokenTypeNames[T_Oper]     = g_symOperator;
    tokenTypeNames[T_Special]  = g_symSpecial;
    tokenTypeNames[T_Symbol]   = g_symSymbol;
    tokenTypeNames[T_EOI]      = g_symEOI;
    tokenTypeNamesCreated      = true;
}

static enum Lexer_LexResult _lexer_nextToken(struct LexerFields* lexerFields) {
    index_t lexemeBufferIndex = 0;
    enum Lexer_State state = S_Init;
    struct Transition* t;
    bool_t consume;
    for (;;) {
        consume = true;
        ichar_t c = *(lexerFields->currentString);
        /* Find the next syntax rule */
        for (t = lexerFields->syntax[state]; !t->charClassPredicate(c); ++t); /* This is the whole loop */
        switch (t->action) {
            case A_Keep:
                lexerFields->lexemeBuffer[lexemeBufferIndex++] = (char)c;
                break;
            case A_Skip:
                break;
            case A_Reuse:
                consume = false;
                break;
            case A_Err:
                return Lexer_UnknownError;
            case A_RealErr:
                return Lexer_RealError;
            case A_StringErr:
                return Lexer_StringError;
            case A_CommentErr:
                return Lexer_StringError;
            default:
                fprintf(stderr, "lexer_next got unhandled action %d\n", t->action);
                assert(false);
                exit(1);
        }
        if (state == S_Init && t->nextState != S_Init) {
            lexerFields->startIndexPos = lexerFields->indexPos;
            lexerFields->startLinePos = lexerFields->linePos;
            lexerFields->startColPos = lexerFields->colPos;
        }
        if (consume) {
            ++lexerFields->currentString;
            ++lexerFields->indexPos;
            ++lexerFields->colPos;
            if (c == '\n') {
                ++lexerFields->linePos;
                lexerFields->colPos = 1;
            }
        }
        state = t->nextState;
        switch (t->tokenType) {
            case T_None:
                break;
            case T_EOI:
                strcpy(lexerFields->lexemeBuffer, "EOI");
                lexemeBufferIndex = 3;
                goto EMIT_TOKEN;
            default:
                goto EMIT_TOKEN;
        }
    }
EMIT_TOKEN:
    lexerFields->lexemeBuffer[lexemeBufferIndex] = 0;
    lexerFields->tokenType = t->tokenType;
    if (t->tokenType == T_Word)
        lexerFields->tokenType = _lexer_classifyWord(lexerFields->lexemeBuffer);
    lexerFields->lexemeLen = lexemeBufferIndex;
    return Lexer_Success;
}

static struct Object* _lexer_lexemeToObject(enum Lexer_TokenType tokenType, string_t lexeme) {
    switch (tokenType) {
        case T_Int:
            return (struct Object*)integer_new(atol(lexeme));
        case T_HexInt:
            return (struct Object*)integer_new(strtol(lexeme, NULL, 16));
        case T_BinInt:
            return (struct Object*)integer_new(strtol(lexeme, NULL, 2));
        case T_Real:
            return (struct Object*)real_new(atof(lexeme));
        case T_Bool:
            return (struct Object*)(strcmp("true", lexeme) ? g_false : g_true);
        case T_Nil:
            return (struct Object*)g_nil;
        case T_Ident:
            return (struct Object*)identifier_new(lexeme);
        case T_Reserved:
            return (struct Object*)string_new(lexeme);
        case T_String:
            return (struct Object*)string_new(lexeme);
        case T_Oper:
            return (struct Object*)identifier_new(lexeme);
        case T_Special:
            return (struct Object*)string_new(lexeme);
        case T_Symbol:
            return (struct Object*)symbol_new(lexeme);
        case T_EOI:
            return (struct Object*)symbol_new(lexeme);
        default:
            fprintf(stderr, "ERROR: unhandled token type in tokenToObject: %d\n", tokenType);
            assert(false);
            exit(1);
    }
}

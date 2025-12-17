#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "lexer/lexer.h"
#include "object/globals.h"
#include "object/types/identifier.h"
#include "object/types/integer.h"
#include "object/types/real.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

// static void _lexError(struct LexerState* lexerState, char* message);
struct Object* _lexemeToObject(enum TokenType tokenType, string_t lexeme);

/* Global variables **********************************************************/

extern char* ReservedWords[];
extern char* BoolWords[];
extern char* NilWord;

#if 0
/* There must be a 1:1 correspondence between this and the StateName enum */
static string_t S_Names[] = {
    "Init", "Integer", "Point", "Real", "Word", "String", "Operator", "Symbol"
};

/* There must be a 1:1 correspondence between this and the Action enum */
static string_t A_Names[] = {
    "Keep", "Reuse", "Skip", "Err", "ErrReal", "ErrString", "ErrComment"
};

/* There must be a 1:1 correspondence between this and the TokenType enum */
static string_t T_Names[] = {
    "None", "Int", "Real", "Bool", "Nil", "Word", "Ident", "Reserved", "String", "Operator", "Special", "Symbol", "EOI"
};
#endif

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

static enum TokenType lexer_classifyWord(char* s) {
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

enum Lexer_LexResult lexer_next(struct Transition** syntax, string_t* inputString, enum TokenType* tokenType, count_t* lexemeLen, string_t lexemeBuffer) {
    index_t lexemeBufferIndex = 0;
    enum StateName state = S_Init;
    struct Transition* t;
    for (;;) {
        ichar_t c = **inputString;
        ++(*inputString);
        t = syntax[state];
        /* find matching transition */
        for (;; ++t) {
            if (t->charClassPredicate(c)) {
                break;  /* TODO place in 'for' header? */
            }
        }
        switch (t->action) {
            case A_Keep:
                lexemeBuffer[lexemeBufferIndex++] = (char)c;
                break;
            case A_Skip:
                break;
            case A_Reuse:
                --(*inputString);
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
        state = t->nextState;
        switch (t->tokenType) {
            case T_None:
                break;
            case T_EOI:
                strcpy(lexemeBuffer, "EOI");
                lexemeBufferIndex = 3;
                goto EMIT_TOKEN;
            default:
                goto EMIT_TOKEN;
        }
    }
EMIT_TOKEN:
    lexemeBuffer[lexemeBufferIndex] = 0;
    *tokenType = t->tokenType;
    if (*tokenType == T_Word)
        *tokenType = lexer_classifyWord(lexemeBuffer);
    *lexemeLen = lexemeBufferIndex;
    return Lexer_Success;
}

static bool_t tokenTypeNamesCreated = false;
static struct Symbol* tokenTypeNames[T_Final];

static void _createTokenTypeNames(void) {
    tokenTypeNames[T_None]     = symbol_new("None");
    tokenTypeNames[T_Int]      = symbol_new("Int");
    tokenTypeNames[T_Real]     = symbol_new("Real");
    tokenTypeNames[T_Bool]     = symbol_new("Bool");
    tokenTypeNames[T_Nil]      = symbol_new("Nil");
    tokenTypeNames[T_Word]     = symbol_new("Word");
    tokenTypeNames[T_Ident]    = symbol_new("Ident");
    tokenTypeNames[T_Reserved] = symbol_new("Reserved");
    tokenTypeNames[T_String]   = symbol_new("String");
    tokenTypeNames[T_Oper]     = symbol_new("Oper");
    tokenTypeNames[T_Special]  = symbol_new("Special");
    tokenTypeNames[T_Symbol]   = symbol_new("Symbol");
    tokenTypeNames[T_EOI]      = symbol_new("EOI");
}

void lexer_lexAll(struct Transition** syntax, const string_t sourceString, struct Vector* tokens) {
    if (!tokenTypeNamesCreated) {
        _createTokenTypeNames();
        tokenTypeNamesCreated = true;
    }
    string_t inputString = sourceString;
    char lexemeBuffer[Lexer_LexemeSize];
    for (;;) {
        enum TokenType tokenType;
        count_t lexemeLen;
        enum Lexer_LexResult res = lexer_next(syntax, &inputString, &tokenType, &lexemeLen, lexemeBuffer);
        #if 0
        fprintf(stderr, "lexer_lexAll got token %d '%s'\n", tokenType, lexemeBuffer);
        #endif
        switch (res) {
            case Lexer_Success: {
                    struct Symbol* tokenTermName = tokenTypeNames[tokenType];
                    struct Object* lexemeObj = _lexemeToObject(tokenType, lexemeBuffer);
                    struct Object* attrib = (struct Object*)g_nil;
                    struct Term* tokenTerm = term_new_1arg(tokenTermName, lexemeObj, attrib);
                    vector_push(tokens, (struct Object*)tokenTerm);
                    if (tokenType == T_EOI) {
                        return;
                    }
                }
                break;
            case Lexer_UnknownError:
                fprintf(stderr, "lexer_lexAll got an unknown error %d\n", res);
                return;
            case Lexer_StringError:
                fprintf(stderr, "lexer_lexAll got a string error %d\n", res);
                return;
            case Lexer_RealError:
                fprintf(stderr, "lexer_lexAll got an real-number error %d\n", res);
                return;
            case Lexer_CommentError:
                fprintf(stderr, "lexer_lexAll got a comment error %d\n", res);
                return;
            default:
                fprintf(stderr, "lexer_lexAll unhandled lex result %d\n", res);
                assert(false);
                return;
        }
    }
}

/* Private functions *********************************************************/

struct Object* _lexemeToObject(enum TokenType tokenType, string_t lexeme) {
    switch (tokenType) {
        case T_Int:
            return (struct Object*)integer_new(atol(lexeme));
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

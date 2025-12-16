#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

enum SpecialChar { C_Nul = 0x00, C_Any = 0xff };

/* Types *********************************************************************/

enum {
    Lexer_LexemeSize = 512
};

enum StateName {
    S_Init, S_Int, S_Point, S_Real, S_Word, S_Str, S_Oper, S_Sym
};

enum Action {
    A_Keep, A_Reuse, A_Skip, A_Err, A_RealErr, A_StringErr, A_CommentErr
} ;

enum TokenType {
    T_None, T_Int, T_Real, T_Bool, T_Nil, T_Word, T_Ident, T_Reserved, T_String, T_Oper, T_Special, T_Symbol, T_EOI, T_Final
};

enum Lexer_LexResult {
    Lexer_Success,
    Lexer_UnknownError,
    Lexer_StringError,
    Lexer_RealError,
    Lexer_CommentError
};

struct Transition {
    bool_t (*charClassPredicate)(ichar_t c);
    enum StateName nextState;
    enum Action    action;
    enum TokenType tokenType;
} ;

struct Lexer {
    const string_t input;
    index_t pos;
    char lexeme[Lexer_LexemeSize];
    count_t lexemeLen;
};

struct Vector;

#if 0
struct Token {
    enum TokenType type;
    index_t pos;
    count_t len;
    index_t line;
    index_t col;
};

struct LexerState {
    struct Transition** syntax;
    string_t inputString;
    index_t  pos;
    index_t  line;
    index_t  col;
    count_t  lexemeLen;
    char     lexeme[Lexer_LexemeSize];
};

struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* The reserved and bool_t words are defined in syntax.h */
extern char* RESERVED_WORDS[];
extern char* BOOL_WORDS[];

/* These State, Action, and Token arrays are defined in lexer.c */
extern char* S_NAMES[];
extern char* A_NAMES[];
extern char* T_NAMES[];

/* Lifecycle functions *******************************************************/

void lexer2_init(struct LexerState* lexerState, struct Transition** syntax, string_t inputString);

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t lexer2_lexAll(const string_t sourceString, struct Vector* tokens, struct Transition** syntax);
struct Transition* lexer2_findTransition(struct Transition** syntax, enum StateName stateName, char_t c);
enum Lexer_LexTokenResult lexer2_lexToken(struct LexerState* lexerState, struct Token* token);

/* Object functions ******************/
#endif

void lexer2_lexAll(struct Transition** syntax, const string_t sourceString, struct Vector* tokens);
enum Lexer_LexResult lexer2_next(struct Transition** syntax, string_t* inputString, enum TokenType* tokenType, count_t* lexemeLen, string_t lexemeBuffer);

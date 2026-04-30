#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

enum SpecialChar { C_Nul = 0x00, C_Any = 0xff };

/* Types *********************************************************************/

enum {
    Lexer_LexemeSize = 512
};

enum Lexer_State {
    S_Init, S_EOI, S_Special, S_Int, S_HexInt, S_BinInt, S_Sign, S_Point, S_Real, S_Word, S_Str, S_Oper, S_Sym, S_Zero
};

enum Lexer_Action {
    A_Keep, A_Reuse, A_Skip, A_Err, A_RealErr, A_StringErr, A_CommentErr
} ;

enum Lexer_TokenType {
    T_None, T_Int, T_HexInt, T_BinInt, T_Real, T_Bool, T_Nil, T_Word, T_Ident, T_Reserved, T_String, T_Oper, T_Special, T_Symbol, T_EOI, T_Final
};

enum Lexer_LexResult {
    Lexer_Success,
    Lexer_UnknownError,
    Lexer_StringError,
    Lexer_RealError,
    Lexer_CommentError,
    Lexer_LexemeLengthError
};

struct Transition {
    bool_t (*charClassPredicate)(ichar_t c);
    enum Lexer_State nextState;
    enum Lexer_Action    action;
    enum Lexer_TokenType tokenType;
} ;

struct Lexer {
    const string_t input;
    index_t pos;
    char lexeme[Lexer_LexemeSize];
    count_t lexemeLen;
};

struct LexerFields;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

struct Vector* lexer_lexAll(struct Transition** syntax, const string_t sourceString);
struct Vector* lexer_lexAll_withVector(struct Transition** syntax, const string_t sourceString, struct Vector* tokens);

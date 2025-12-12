#pragma once

#include "_typedefs.h"

#define LEXEME_SIZE 16

/* The reserved and bool_t words are defined in syntax.h */
extern char* RESERVED_WORDS[];
extern char* BOOL_WORDS[];

/* These State, Action, and Token arrays are defined in lexer.c */
extern char* S_NAMES[];
extern char* A_NAMES[];
extern char* T_NAMES[];

typedef enum {
    S_I, S_INT, S_POINT, S_REAL, S_WORD, S_STR, S_OPER, S_SYM
} StateName;

typedef enum {
    A_KEEP, A_REUSE, A_IGNORE, A_DOUBLEDOT, A_ERR, A_ERR_REAL, A_ERR_STRING
} Action;

typedef enum {
    T_NONE, T_INT, T_REAL, T_BOOL, T_WORD, T_IDENT, T_RESERVED, T_STRING, T_OPER, T_SPECIAL, T_SYMBOL, T_EOI
} TokenType;

#define C_NUL ((char)0x00)
#define C_ANY ((char)0xff)

typedef struct {
    char from, to;
    StateName nextState;
    Action action;
    TokenType tokenType;
} Transition;

typedef struct {
    char lexeme[LEXEME_SIZE];
    int pos;
    int line;
    int col;
    TokenType type;
} Token;

typedef struct {
    Transition** syntax;
    Object inputString;
    int inputLen;
    int pos;
    int line;
    int col;
    bool_t error;
} LexerState;

Transition* findTransition(Transition** syntax, StateName stateName, char c);
bool_t isIn(char* str, char* strAry[]);
void lexInit(LexerState* lexerState, Transition** syntax, Object inputString);
bool_t lexToken(Thread* thd, LexerState* lexerState, Token* token);

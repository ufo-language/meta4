#pragma once

#include "_typedefs.h"

/* Defines ------------------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

enum TokenType {
    TOK_INT,
    TOK_FLOAT,
    TOK_IDENT,
    TOK_SYMBOL,
    TOK_STRING,
    TOK_OPERATOR,
    TOK_SPECIAL,
    TOK_EOF,
    TOK_ERROR
};

struct LexerToken {
    enum TokenType type;
    const char* start;
    count_t length;
};

/* Forward declarations -----------------------------------------------------*/

/* Global variables ---------------------------------------------------------*/

/* Lifecycle functions ------------------------------------------------------*/

/* Public functions ---------------------------------------------------------*/

void lexer2_lexAll(const char* string);
struct LexerToken lexer_nextToken(const char** pcur);

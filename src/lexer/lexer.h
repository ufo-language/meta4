#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum LexerTokenType {
    TOK_INT_DEC,
    TOK_INT_HEX,
    TOK_INT_BIN,
    TOK_FLOAT,
    TOK_IDENT,
    TOK_SYMBOL,
    TOK_STRING,
    TOK_OPERATOR,
    TOK_SPECIAL,
    TOK_EOF
};

struct LexerToken {
    enum LexerTokenType type;
    const char* start;
    count_t length;
};

struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

bool_t lexer_lexAll(const char* sourceString, struct Vector* tokens);

/* Object functions ******************/

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum LexerTokenType {
    TOK_INT,
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

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

void lexer_lexAll(const char* src);

/* Object functions ******************/

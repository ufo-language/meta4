#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct Symbol;
struct Vector;

enum ParseStatus {
    PS_Success,
    PS_Fail,
    PS_Error
};

typedef enum ParseStatus (*ParserFunction)(struct Vector* tokens, index_t* tokenIndex, struct Object** result);

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pIgnore(ParserFunction parser, struct Vector* tokens, index_t* tokenIndex, struct Object** result);
enum ParseStatus pOneOf(count_t nParsers, ParserFunction parsers[], struct Vector* tokens, index_t* tokenIndex, struct Object** result);
enum ParseStatus pSequence(count_t nParsers, ParserFunction parsers[], struct Vector* tokens, index_t* tokenIndex, struct Object** result);
enum ParseStatus pSpot(struct Symbol* tokenType, struct Vector* tokens, index_t* tokenIndex, struct Object** result);

/* Composable parsers */

enum ParseStatus pStrip(struct Vector* tokens, index_t* tokenIndex, struct Object** result);

/* Private functions *********************************************************/

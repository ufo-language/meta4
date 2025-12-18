#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct Symbol;
struct Vector;

typedef bool_t (*ParserFunction)(struct Vector* tokens, index_t* tokenIndex, struct Object** result);


/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t pSequence(count_t nParsers, ParserFunction parsers[], struct Vector* tokens, index_t* tokenIndex, struct Object** result);
bool_t pSpot(struct Symbol* tokenType, struct Vector* tokens, index_t* tokenIndex, struct Object** result);

/* Composable parsers */

bool_t pStrip(struct Vector* tokens, index_t* tokenIndex, struct Object** result);

/* Private functions *********************************************************/

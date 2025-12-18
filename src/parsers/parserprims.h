#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Symbol;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

bool_t pSpot(struct Symbol* tokenType, struct Vector* tokens, index_t* tokenIndex, struct Vector* results);
bool_t pStrip(struct Vector* tokens, index_t* tokenIndex, struct Vector* results);

/* Private functions *********************************************************/

#include "_typedefs.h"

#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pReservedEnd(struct ParseState* parseState);
enum ParseStatus pSpotReserved(const string_t word, struct ParseState* parseState);

/* Private functions *********************************************************/

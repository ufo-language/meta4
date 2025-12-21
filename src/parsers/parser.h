#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum ParseStatus {
    PS_Success,
    PS_Fail,
    PS_Error
};

struct Object;
struct Vector;

struct ParseState {
    struct Vector* tokens;
    index_t index;
    struct Object* result;
};

typedef enum ParseStatus (*ParserFunction)(struct ParseState* parseState);

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/

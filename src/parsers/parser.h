#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum ParseStatus {
    PS_Success,
    PS_Fail,
    PS_Error
};

struct IntVector;
struct Object;
struct Vector;

struct ParseState {
    struct Vector* tokens;
    index_t index;
    struct Object* result;
    struct IntVector* memoVector;
};

struct Vector;

typedef enum ParseStatus (*ParserFunction)(struct ParseState* parseState);

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ParseState* parseState_new(struct Vector* tokens);
void parseState_init(struct ParseState* parseState, struct Vector* tokens);

/* Public functions **********************************************************/

enum ParseStatus parse(ParserFunction parser, struct ParseState* parseState);

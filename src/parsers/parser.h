#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum ParseResultStatus {
    PRS_Pass,
    PRS_Fail,
    PRS_Error
};

struct IntVector;
struct Object;
struct Vector;

struct ParseState {
    struct Vector* tokens;
    index_t index;
    struct Object* result;
    struct Vector* memoVector;
};

struct Vector;

typedef enum ParseResultStatus (*ParserFunction)(struct ParseState* parseState);

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct ParseState* parseState_new(struct Vector* tokens);
void parseState_init(struct ParseState* parseState, struct Vector* tokens);

/* Public functions **********************************************************/

enum ParseResultStatus parse(ParserFunction parser, struct ParseState* parseState);

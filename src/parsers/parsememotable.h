#pragma once

#include "_typedefs.h"

#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

void parser_addRecursionBarrier(ParserFunction parserFunction, struct ParseState* parseState);

bool_t parser_memoLookup(struct Vector* memoVector,
                         ParserFunction parserFunction,
                         index_t tokenIndex,
                         enum ParseResultStatus* status,
                         struct Object** resultObj);

void parser_memoizeResult(struct Vector* memoVector,
                          ParserFunction parserFunction,
                          index_t tokenIndex,
                          enum ParseResultStatus status,
                          struct Object* resultObj);

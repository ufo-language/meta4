#pragma once

#include "_typedefs.h"

#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pArray(struct ParseState* parseState);
enum ParseResultStatus pBinding(struct ParseState* parseState);
enum ParseResultStatus pHashTable(struct ParseState* parseState);
enum ParseResultStatus pPair(struct ParseState* parseState);
enum ParseResultStatus pQueue(struct ParseState* parseState);
enum ParseResultStatus pSet(struct ParseState* parseState);
enum ParseResultStatus pTerm(struct ParseState* parseState);
enum ParseResultStatus pVector(struct ParseState* parseState);

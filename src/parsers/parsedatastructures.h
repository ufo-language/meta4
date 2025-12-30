#pragma once

#include "_typedefs.h"

#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pArray(struct ParseState* parseState);
enum ParseStatus pBinding(struct ParseState* parseState);
enum ParseStatus pHashTable(struct ParseState* parseState);
enum ParseStatus pPair(struct ParseState* parseState);
enum ParseStatus pQueue(struct ParseState* parseState);
enum ParseStatus pSet(struct ParseState* parseState);
enum ParseStatus pTerm(struct ParseState* parseState);
enum ParseStatus pVector(struct ParseState* parseState);

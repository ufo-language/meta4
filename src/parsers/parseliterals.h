#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

#include "_typedefs.h"

#include "object/globals.h"
#include "parsers/parserprims.h"
#include "parsers/parsestate.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pBoolean(struct ParseState* parseState);
enum ParseStatus pEOI(struct ParseState* parseState);
enum ParseStatus pIdentifier(struct ParseState* parseState);
enum ParseStatus pInteger(struct ParseState* parseState);
enum ParseStatus pNil(struct ParseState* parseState);
enum ParseStatus pReal(struct ParseState* parseState);
enum ParseStatus pString(struct ParseState* parseState);
enum ParseStatus pSymbol(struct ParseState* parseState);
